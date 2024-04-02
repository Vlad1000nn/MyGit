import tkinter as tk
import sqlite3 as sql
from typing import TextIO


log_file: TextIO = None

user_db: sql.Connection = None
journal_db: sql.Connection = None

user_cursor: sql.Cursor = None
journal_cursor: sql.Cursor = None

root: tk.Tk = None

start_hello_label: tk.Label = None
start_enter_button: tk.Button = None
start_registration_button: tk.Button = None

registration_hello_label: tk.Label = None
registration_entry_name: tk.Entry = None
registration_entry_password: tk.Entry = None
registration_add_button: tk.Button = None


def start_registration_button_click():
    print('Кнопка регистрации нажата')
    log_file.write('Кнопка регистрации нажата\n')
    hide_start_page()
    show_registration_page()


def start_enter_button_click():
    print('Кнопка входа нажата')


def registration_add_button_click():
    print('Кнопка применить нажата')
    user_cursor.execute("INSERT INTO users(name,password) VALUES(?,?)",
                        (registration_entry_name.get(), registration_entry_password.get()))
    user_db.commit()


def show_start_page():
    start_hello_label.place(relx=0.5, rely=0.2, anchor='center')
    start_registration_button.place(relx=0.5, rely=0.35, anchor='center')
    start_enter_button.place(relx=0.5, rely=0.55, anchor='center')


def show_registration_page():
    registration_hello_label.place(relx=0.5, rely=0.2, anchor='center')
    registration_entry_name.place(relx=0.5, rely=0.35, anchor='center')
    registration_entry_password.place(relx=0.5, rely=0.5, anchor='center')
    registration_add_button.place(relx=0.5, rely=0.6, anchor='center')


def show_enter_page():
    pass


def hide_start_page():
    start_hello_label.place_forget()
    start_registration_button.place_forget()
    start_enter_button.place_forget()


def hide_registration_page():
    registration_hello_label.place_forget()
    registration_entry_name.place_forget()
    registration_entry_password.place_forget()
    registration_add_button.place_forget()


def init_window():
    global root
    root = tk.Tk()
    root.geometry('1920x1080')
    root.title('Стартовое окно')
    root.iconbitmap('start_window.ico')
    root['bg'] = '#37474F'


def init_start_page():
    global start_hello_label
    global start_registration_button
    global start_enter_button

    start_hello_label = tk.Label(root, text='Приветствуем!', font=('cursive', 20), fg ='blue', bg=root['bg'])

    start_registration_button = tk.Button(root, text='Регистрация', command=start_registration_button_click,
                                          font='cursive', fg='blue', bg='#F48FB1', activebackground='white',
                                          activeforeground='yellow', height=3, width=25)

    start_enter_button = tk.Button(root, text='Вход', command=start_enter_button_click, font='cursive',
                                   fg='blue', bg='#F48FB1', activebackground='white',
                                   activeforeground='yellow', height=3, width=25)

    start_hello_label.place(relx=0.5, rely=0.2, anchor='center')
    start_registration_button.place(relx=0.5, rely=0.35, anchor='center')
    start_enter_button.place(relx=0.5, rely=0.55, anchor='center')


def init_registration_page():
    global registration_hello_label
    global registration_entry_name
    global registration_entry_password
    global registration_add_button

    registration_hello_label = tk.Label(root, text='Регистрация', font=('cursive', 20), fg='blue', bg=root['bg'])

    registration_add_button = tk.Button(root, text='применить', command=registration_add_button_click, font='cursive',
                                        fg='blue', bg='#F48FB1', activebackground='white',
                                        activeforeground='yellow', height=3, width=25)
    registration_entry_name = tk.Entry(root)
    registration_entry_password = tk.Entry(root, show='*')


def init_enter_page():
    pass


def create_user_table():
    user_cursor.execute("CREATE TABLE IF NOT EXISTS users(user_id INTEGER PRIMARY KEY, name TEXT, password TEXT)")


def connect_to_db(db_name):
    try:
        database = sql.connect(db_name)
        print('База данных', db_name, 'подключена')
        print('Курсор', db_name, 'подключён')
    except sql.Error as error:
        print('Ошибка подключения к базе данных:', error)
        database = None
    return database, database.cursor()


def clear(*args):
    current_name = ""
    for current in args:
        if isinstance(current, str):
            current_name = current
            continue
        if isinstance(current, sql.Connection):
            if current is not None:
                current.close()
                print('База данных ', current_name, ' успешно закрыта')
                log_file.write('База данных ' + str(current_name) + ' успешно закрыта\n')
        elif isinstance(current, sql.Cursor):
            if current is not None:
                current.close()
                print('Курсор ', current_name, ' успешно закрыт')
                log_file.write('Курсор ' + str(current_name) + ' успешно закрыт\n')
        else:
            print('Неизвестный объект, не удалось закрыть')
            log_file.write('Неизвестный объект, не удалось закрыть\n')


def main():

    # Файл для записывания логов
    global log_file
    log_file = open('main.log', 'w')
    if not log_file.closed:
        print('Файл с логами открылся')
        log_file.write('Успешное открытие\n')
    else:
        print('Файл с логами не открылся')
        exit()

    # Создаём окно
    global root
    init_window()

    # Инициализируем страницы
    init_start_page()
    init_registration_page()
    init_enter_page()

    # Добавляем интерфейс стартовой страницы
    show_start_page()

    # Теперь подключаем базы данных пользователей и журнализации(действия над базой пользователей)
    global user_db
    global user_cursor
    global journal_db
    global journal_cursor

    user_db, user_cursor = connect_to_db('users.db')
    if user_db is None:
        exit()
    create_user_table()

    journal_db, journal_cursor = connect_to_db('journal.db')
    if journal_db is None:
        clear('user', user_db, user_cursor)
        exit()

    # Запускаем окно
    root.mainloop()

    # Запрос для себя
    user_cursor.execute("SELECT * FROM users")
    print(user_cursor.fetchall())

    # Закрываем все БД
    clear('user', user_cursor, user_db, 'journal', journal_cursor, journal_db)

    # Закрываем файл с логами
    log_file.close()
    if log_file.closed:
        print('Файл с логами успешно закрылся')
    else:
        print('Файл с логами не закрылся')


if __name__ == "__main__":
    main()
