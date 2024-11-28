import os
import subprocess

baglama = 0
isletimsistemi = 1  # 1: Windows, 2: Linux, 3: macOS

# Şu anki dizindeki .cpp dosyalarını bul
def find_cpp_file():
    for file in os.listdir():
        if file.endswith(".cpp"):
            return file
    return None

# C++ dosyasını derleme ve çalıştırma
def compile_and_run_cpp():
    cpp_file = find_cpp_file()
    if cpp_file is None:
        print("Hiçbir C++ dosyası bulunamadı.")
        return
    
    object_file = cpp_file.replace(".cpp", ".o")
    output_file = cpp_file.replace(".cpp", ".exe") if isletimsistemi == 1 else cpp_file.replace(".cpp", "")  # Windows için .exe, diğerleri için çıkış dosyası uzantısız

    try:
        # g++ ile derleme
        compile_command = f"g++ -Isrc/include -c {cpp_file}"
        subprocess.run(compile_command, shell=True, check=True)
        
        # Bağlama
        if baglama == 0:
            link_command = f"g++ -std=c++17 {object_file} -o {output_file} -Lsrc/lib -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -mwindows -lstdc++fs"
        elif baglama == 1:
            link_command = f"g++ -std=c++17 {object_file} -o {output_file} -Lsrc/lib -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -lstdc++fs"

        # İşletim sistemine göre ayar
        if isletimsistemi == 1:  # Windows
            link_command += " -mwindows"
        elif isletimsistemi == 2:  # Linux
            link_command += ""
        elif isletimsistemi == 3:  # macOS
            link_command += " -framework sfml-graphics -framework sfml-window -framework sfml-system -framework sfml-audio"

        subprocess.run(link_command, shell=True, check=True)

        # Çalıştırma
        if isletimsistemi == 1:  # Windows
            run_command = f".\\{output_file}"
        else:  # Linux ve macOS
            run_command = f"./{output_file}"
        subprocess.run(run_command, shell=True)

    except subprocess.CalledProcessError as e:
        print(f"Bir hata oluştu: {e}")

if __name__ == "__main__":
    compile_and_run_cpp()
