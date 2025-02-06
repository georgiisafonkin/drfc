import socket
import random
import string
import struct
import time

# Функция для генерации случайного текста длиной (105 - 5 = 100) символов
def generate_random_message():
    return ''.join(random.choices(string.ascii_letters + string.digits, k=1024))

# Функция для формирования пакета
def create_packet(packet_number):
    # Генерируем сообщение
    message = generate_random_message()

    # Формируем пакет с требуемой структурой
    packet = bytearray(1024 + 5)

    # Первый байт нулевой
    packet[0] = 0

    # Следующие четыре байта - номер пакета в Big Endian
    packet[1:3] = struct.pack('>H', packet_number)  # >H - Big Endian 2 байта (unsigned short)

    # Остальные 100 байт заполняются случайным сообщением
    packet[3:] = message.encode('latin-1')[:102]  # Используем latin-1, если это ваша кодировка

    return packet

# Создаем UDP-сокет для приема стартового сообщения
def start_udp_server():
    server_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    server_socket.bind(('localhost', 7070))
    print("Ожидаем стартовое сообщение...")

    # Получаем стартовое сообщение
    data, addr = server_socket.recvfrom(1024)

    try:
        # Декодируем сообщение с нужной кодировкой
        print(f"Получено стартовое сообщение от {addr}: {data}")
    except UnicodeDecodeError:
        print(f"Ошибка декодирования данных: получены не latin-1 данные от {addr}")

    return server_socket, addr

# Функция для отправки трех сообщений
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
