import asyncio
import os
import aiohttp
from prettytable import PrettyTable

def get_file_save_path():
    while True:
        save_directory_path = input("Введи путь к директории для сохранения файлов: ")
        # save_directory_path = os.path.abspath(save_directory_path)  # Полный абсолютный путь
        if not os.path.exists(save_directory_path):
            print("Прости, пир, папка не существует... ")
            continue
        elif not os.path.isdir(save_directory_path):
            print("Прости, пир, но это не папка... ")
            continue
        elif not os.access(save_directory_path, os.W_OK):
            print("Прости, пир, у меня нет прав на запись... ")
            continue
        else:
            # print(f"Файлы будут сохранены в: {save_directory_path}")
            return save_directory_path

async def get_url_from_user(queue: asyncio.Queue):
    print ("Вводи построчно url изображений для даунлоада (пустая строка для завершения): ")
    while True:
        # python 3.9 => ввод выводим в отдельный поток, чтобы не блокировал поток исполнения
        url = (await asyncio.to_thread(input)).strip()
        # print(f"Введено: '{url}'")
        if not url:
            await queue.put(None) 
            break
        else:
            await queue.put(url)

async def download_url_from_queue(queue: asyncio.Queue, results_log, save_path: str):
    async with aiohttp.ClientSession() as session:
        while True:
            url = await queue.get()
            try:
                if url is None:
                    break
                success_status = False

                async with session.get(url, timeout=3) as response:
                    if response.status == 200:
                        file = await response.read()
                        filename = url.split('/')[-1]
                        full_path = os.path.join(save_path, filename)
                        with open(full_path, 'wb') as f:
                            f.write(file)
                        success_status = True
                        results_log[url] = success_status
            except:
                    results_log[url] = success_status
            finally:
                queue.task_done()

def draw_table(dict):
    t = PrettyTable()
    # t.title = "URL success status"
    t.field_names = ["URL", "Success status"]
    for key in dict.keys():
        t.add_row([key, dict[key]])
    print(t)

async def main():
    print("Установка зависимостей:\npip install -r requirements.txt")

    save_path = get_file_save_path()

    queue = asyncio.Queue()
    success_log = {}

    # Создаем и запускаем задачи
    urls_creator = asyncio.create_task(get_url_from_user(queue))
    urls_downloader = asyncio.create_task(download_url_from_queue(queue, success_log, save_path))

    # ждем завершения ввода url-ов
    await urls_creator
    # ждем окончания скачивания
    # await queue.join()
    await urls_downloader
    # печатаем результаты
    draw_table(success_log)

if __name__ == "__main__":
    asyncio.run(main())
