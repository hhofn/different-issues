#include <iostream>
#include <oci.h>
#include <mongocxx/client.hpp>
#include <mongocxx/stdx.hpp>
#include <mongocxx/uri.hpp>

OCIEnv *myenv;
OCISvcCtx *mysvcctx;
OCIError *myerr;
OCIStmt   *stmt;
OCIDefine *defn1 = (OCIDefine *) 0;

void handleError() {
    text errbuf[512];
    sb4 errcode = 0;
    OCIErrorGet((dvoid *)myerr, (ub4) 1, (text *) NULL, &errcode, errbuf, (ub4) sizeof(errbuf), OCI_HTYPE_ERROR);
    fprintf(stderr, "Oracle error: %s\n", errbuf);
    exit(1);
}

void connectToOracle() {
    if (OCIInitialize((ub4) OCI_DEFAULT, (dvoid *)0, (dvoid * (*)(dvoid *, size_t)) 0, (dvoid * (*)(dvoid *, dvoid *, size_t))0, (void (*)(dvoid *, dvoid *)) 0) != OCI_SUCCESS)
        handleError();

    if (OCIEnvInit( (OCIEnv **) &myenv, OCI_DEFAULT, (size_t) 0, (dvoid **) 0 ) != OCI_SUCCESS)
        handleError();

    if (OCIHandleAlloc((dvoid *) myenv, (dvoid **) &myerr, OCI_HTYPE_ERROR, (size_t) 0, (dvoid **) 0) != OCI_SUCCESS)
        handleError();

    if (OCILogon(myenv, myerr, &mysvcctx, (const OraText *) "username", (ub4) strlen("username"), (const OraText *) "password", (ub4) strlen("password"), (const OraText *) "DBName", (ub4) strlen("DBName")) != OCI_SUCCESS)
        handleError();
}

void fetchCO2Data() {
    text *select_sql = (text *)"SELECT column_name FROM table_name"; // replace with your SQL query

    if (OCIStmtPrepare(stmt, myerr, select_sql, (ub4) strlen((char *)select_sql), (ub4) OCI_NTV_SYNTAX, (ub4) OCI_DEFAULT) != OCI_SUCCESS)
        handleError();

    // Assuming a single column data fetch for simplicity. For multiple columns, use multiple defines.
    int data;
    if (OCIDefineByPos(stmt, &defn1, myerr, 1, (dvoid *) &data, sizeof(data), SQLT_INT, (dvoid *) 0, (ub2 *)0, (ub2 *)0, OCI_DEFAULT) != OCI_SUCCESS)
        handleError();

    // Execute the SQL query
    if (OCIStmtExecute(mysvcctx, stmt, myerr, (ub4) 1, (ub4) 0, (CONST OCISnapshot *) NULL, (OCISnapshot *) NULL, OCI_DEFAULT) != OCI_SUCCESS)
        handleError();
    
    while (OCIStmtFetch2(stmt, myerr, 1, OCI_FETCH_NEXT, 0, OCI_DEFAULT) != OCI_NO_DATA) {
        // Use fetched data
        // For this example, I'm just printing the data
        std::cout << "Data: " << data << std::endl;
    }
}

void migrateToMongoDB() {
    try {
        mongocxx::uri uri("mongodb://localhost:27017");
        mongocxx::client client(uri);

        mongocxx::database db = client["carbonDB"];
        mongocxx::collection coll = db["emissions"];

        bsoncxx::builder::stream::document document{};
        
        // Sample data (replace this with actual fetched data)
        document << "city" << "Stockholm" << "year" << 2021 << "emission" << 5000;

        coll.insert_one(document.view());
    } catch(const std::exception &e) {
        std::cerr << "MongoDB error: " << e.what() << std::endl;
    }
}

int main() {
    connectToOracle();
    fetchCO2Data();
    migrateToMongoDB();
    return 0;
}
