from pydub import AudioSegment
import numpy as np
import librosa

def detect_beats(file_path):
    # Загрузка аудиофайла
    y, sr = librosa.load(file_path, sr=None)
    
    # Использование функции librosa для обнаружения ударов
    tempo, beat_frames = librosa.beat.beat_track(y=y, sr=sr)
    beat_times = librosa.frames_to_time(beat_frames, sr=sr)
    
    return beat_times

def main():
    file_path = '/Users/hofn/Library/CloudStorage/GoogleDrive-vasilii.katana@gmail.com/My Drive/music/mix/Music/Unknown Artist/Unknown Album/bohuslän_podcast_#1.m4a'
    
    # Конвертируем файл в WAV для удобства обработки
    audio = AudioSegment.from_file(file_path, format="m4a")
    wav_path = '/Users/hofn/Library/CloudStorage/GoogleDrive-vasilii.katana@gmail.com/My Drive/music/mix/Music/Unknown Artist/Unknown Album/temporary_file.wav'
    audio.export(wav_path, format="wav")
    
    # Получаем время ударов
    beat_times = detect_beats(wav_path)
    
    # Печать времени ударов
    for i, beat_time in enumerate(beat_times):
        print(f'Beat {i+1}: {beat_time:.2f} seconds')

if __name__ == "__main__":
    main()
