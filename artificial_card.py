import socket
import random
import struct
import time

# Функция для генерации рефлектограммы (массив случайных чисел)
def generate_reflectogram(size):
    # Генерируем массив случайных 16-битных чисел (от 0 до 65535)
    return [random.randint(0, 65535) for _ in range(size // 2)]

# Функция для формирования пакета
def create_packet(packet_number):
    # Размер сообщения 1024 + 5 байт (5 байт заголовка + рефлектограмма)
    packet = bytearray(1029)

    # Первый байт нулевой
    packet[0] = 0

    # Следующие четыре байта - номер пакета в Big Endian
    packet[1:3] = struct.pack('>H', packet_number)

    # Генерируем рефлектограмму
    reflectogram = generate_reflectogram(1019)

    # Заполняем байты начиная с шестого двухбайтовыми значениями рефлектограммы
    for i, value in enumerate(reflectogram):
        start = 5 + i * 2
        packet[start:start + 2] = struct.pack('>H', value)

    return packet

# Создаем UDP-сокет для приема стартового сообщения
def start_udp_server():
    server_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    server_socket.bind(('localhost', 7070))
    print("Ожидаем стартовое сообщение...")

    # Получаем стартовое сообщение
    data, addr = server_socket.recvfrom(1024)

    try:
        print(f"Получено стартовое сообщение от {addr}: {data}")
    except UnicodeDecodeError:
        print(f"Ошибка декодирования данных: получены данные в неизвестной кодировке от {addr}")

    return server_socket, addr

# Функция для отправки трёх сообщений
def send_three_messages(server_socket, addr):
    for msg_number in range(1, 4):
        print(f"Отправка сообщения {msg_number} на {addr}...")

        # Отправляем три пакета для каждого сообщения
        for packet_number in range(0, 3):
            packet = create_packet(packet_number)
            server_socket.sendto(packet, addr)
            time.sleep(1)  # Пауза между пакетами

        print(f"Сообщение {msg_number} отправлено.")

# Основная программа
def main():
    server_socket, addr = start_udp_server()

    # Отправляем три сообщения
    send_three_messages(server_socket, addr)

    server_socket.close()

if __name__ == "__main__":
    main()
