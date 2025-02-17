import struct

def read_bin_write_txt(bin_filename, txt_filename):
    try:
        with open(bin_filename, "rb") as bin_file, open(txt_filename, "w") as txt_file:
            while True:
                data = bin_file.read(2)  # Читаем 2 байта
                if len(data) < 2:  # Проверяем, что данных достаточно
                    break
                number = struct.unpack(">H", data)[0]  # Распаковываем как беззнаковое целое (little-endian)
                txt_file.write(f"{number}\n")  # Записываем в файл
        print(f"Данные успешно записаны в {txt_filename}")
    except Exception as e:
        print(f"Ошибка: {e}")

# Пример использования
read_bin_write_txt("./build/reflectogram_1.bin", "reflectogram_1.txt")
