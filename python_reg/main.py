import tkinter as tk
import sqlite3 as sql
from typing import TextIO
import time

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

registration_error_label: tk.Label = None
registration_empty_name_error_label: tk.Label = None
registration_empty_password_error_label: tk.Label = None

enter_page_hello_label: tk.Label = None
enter_page_entry_name: tk.Entry = None
enter_page_entry_password: tk.Entry = None
enter_page_enter_button: tk.Button = None

enter_page_error_label: tk.Label = None
enter_page_empty_name_error_label: tk.Label = None
enter_page_empty_password_error_label: tk.Label = None

current_user = None


def start_registration_button_click():
    log_file.write('Кнопка регистрации нажата\n')
    hide_start_page()
    show_registration_page()


def start_enter_button_click():
    log_file.write('Кнопка входа нажата\n')
    hide_start_page()
    show_enter_page()


def enter_page_enter_button_click():
    global current_user

    log_file.write('Кнопка войти нажата\n')
    enter_name = enter_page_entry_name.get()
    enter_password = enter_page_entry_password.get()

    if enter_name == "":
        enter_page_empty_name_error_label.place(relx=0.5, rely=0.37, anchor='center')
        log_file.write('Пустое имя при попытке входа\n')
    else:
        enter_page_empty_name_error_label.place_forget()

    if enter_password == "":
        registration_empty_password_error_label.place(relx=0.5, rely=0.42, anchor='center')
        log_file.write('Пустой пароль при регистрации\n')
    else:
        enter_page_empty_password_error_label.place_forget()

    user_cursor.execute("SELECT user_id, password FROM users WHERE name = ?", (enter_name,))
    user_info = user_cursor.fetchone()

    if user_info is None or user_info[1] != enter_password:
        enter_page_error_label.place(relx=0.5, rely=0.8, anchor='center')
    else:
        enter_page_error_label.place_forget()
        hide_enter_page()
        current_user = user_info[0]
        show_app_page()


def registration_add_button_click():
    log_file.write('Кнопка применить нажата\n')
    new_name = registration_entry_name.get()
    new_password = registration_entry_password.get()

    if new_name == "":
        registration_empty_name_error_label.place(relx=0.5, rely=0.37, anchor = 'center')
        log_file.write('Пустое имя при регистрации\n')
    else:
        registration_empty_name_error_label.place_forget()

    if new_password == "":
        registration_empty_password_error_label.place(relx=0.5, rely=0.42, anchor='center')
        log_file.write('Пустой пароль при регистрации\n')
    else:
        registration_empty_password_error_label.place_forget()

    user_cursor.execute("SELECT * FROM users WHERE name = ?", (new_name,))
    if user_cursor.fetchone() is not None:
        registration_error_label.place(relx=0.5, rely=0.8, anchor='center')
        log_file.write('Попытка зарегистрировать уже существующего пользователя')
        return
    registration_error_label.place_forget()

    if new_name != "" and new_password != "":
        users_insert(new_name, new_password)

        hide_registration_page()
        show_start_page()

        success_window = tk.Toplevel(root)
        success_window.title('')
        success_window.geometry('400x150')
        success_window['bg'] = '#37474F'

        success_label = tk.Label(success_window, text='Регистрация прошла успешно!', font=('cursive', 20), fg='blue',
                            bg=success_window['bg'])
        success_label.place(relx=0.5, rely=0.3, anchor='center')

        success_button = tk.Button(success_window, text='OK', command=success_window.destroy, font='cursive', fg='blue',
                                   bg='#F48FB1', activebackground='white', activeforeground='yellow', height=3, width=25)
        success_button.place(relx=0.5, rely=0.7, anchor='center')


def show_start_page():
    start_hello_label.place(relx=0.5, rely=0.2, anchor='center')
    start_registration_button.place(relx=0.5, rely=0.35, anchor='center')
    start_enter_button.place(relx=0.5, rely=0.55, anchor='center')


def show_registration_page():
    registration_hello_label.place(relx=0.5, rely=0.2, anchor='center')
    registration_entry_name.place(relx=0.5, rely=0.35, anchor='center')
    registration_entry_password.place(relx=0.5, rely=0.4, anchor='center')
    registration_add_button.place(relx=0.5, rely=0.5, anchor='center')


def show_enter_page():
    enter_page_hello_label.place(relx=0.5, rely=0.2, anchor='center')
    enter_page_entry_name.place(relx=0.5, rely=0.35, anchor='center')
    enter_page_entry_password.place(relx=0.5, rely=0.4, anchor='center')
    enter_page_enter_button.place(relx=0.5, rely=0.5, anchor='center')


def show_app_page():
    global current_user


def hide_start_page():
    start_hello_label.place_forget()
    start_registration_button.place_forget()
    start_enter_button.place_forget()


def hide_registration_page():
    registration_hello_label.place_forget()
    registration_entry_name.place_forget()
    registration_entry_password.place_forget()
    registration_add_button.place_forget()


def hide_enter_page():
    enter_page_hello_label.place_forget()
    enter_page_enter_button.place_forget()
    enter_page_entry_name.place_forget()
    enter_page_entry_password.place_forget()


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
    global registration_error_label
    global registration_empty_name_error_label
    global registration_empty_password_error_label

    registration_hello_label = tk.Label(root, text='Регистрация', font=('cursive', 20), fg='blue', bg=root['bg'])

    registration_add_button = tk.Button(root, text='применить', command=registration_add_button_click, font='cursive',
                                        fg='blue', bg='#F48FB1', activebackground='white',
                                        activeforeground='yellow', height=3, width=25)
    registration_entry_name = tk.Entry(root)
    registration_entry_password = tk.Entry(root, show='*')

    registration_error_label = tk.Label(root, text='Данный пользователь уже существует', font=('cursive', 20),
                                        bg=root['bg'], fg='red')
    registration_empty_name_error_label = tk.Label(root, text='Имя пользователя не может быть пустым',
                                                   font=('cursive', 10), bg=root['bg'], fg='red')
    registration_empty_password_error_label = tk.Label(root, text='Пароль не может быть пустым',
                                                       font=('cursive', 10), bg=root['bg'], fg='red')


def init_enter_page():
    global enter_page_hello_label
    global enter_page_enter_button
    global enter_page_entry_name
    global enter_page_entry_password
    global enter_page_error_label
    global enter_page_empty_name_error_label
    global enter_page_empty_password_error_label

    enter_page_hello_label = tk.Label(root, text='Вход', font=('cursive', 20), fg='blue', bg=root['bg'])

    enter_page_enter_button = tk.Button(root, text='войти', command=enter_page_enter_button_click, font='cursive',
                                        fg='blue', bg='#F48FB1', activebackground='white',
                                        activeforeground='yellow', height=3, width=25)
    enter_page_entry_name = tk.Entry(root)
    enter_page_entry_password = tk.Entry(root, show='*')

    enter_page_error_label = tk.Label(root, text='Неверное имя пользователя или пароль', font=('cursive', 20),
                                      bg=root['bg'], fg='red')
    enter_page_empty_name_error_label = tk.Label(root, text='Имя пользователя не может быть пустым',
                                                 font=('cursive', 10), bg=root['bg'], fg='red')
    enter_page_empty_password_error_label = tk.Label(root, text='Пароль не может быть пустым',
                                                     font=('cursive', 10), bg=root['bg'], fg='red')


# Делаем вставку в users и journal
def users_insert(name, password):
    user_cursor.execute("INSERT INTO users(name, password) VALUES (?, ?)", (name, password))
    user_cursor.execute("SELECT user_id FROM users WHERE name = ?", (name,))
    user_id = user_cursor.fetchall()

    journal_cursor.execute("INSERT INTO journal(type, user_id, name, password) VALUES (?, ?, ?, ?)",
                           ("INSERT", user_id[0][0], name, password))
    user_db.commit()
    journal_db.commit()


# Изменяем пароль для user и записываем в journal
def users_update(name, password):
    user_cursor.execute("UPDATE users SET password = ? WHERE name = ?", (password, name))
    user_cursor.execute("SELECT user_id FROM users WHERE name = ?", (name,))
    user_id = user_cursor.fetchall()
    journal_cursor.execute("INSERT INTO journal(type, user_id, name, password) VALUES (?, ?, ?, ?)",
                           ("UPDATE", user_id[0][0], name, password))
    user_db.commit()
    journal_db.commit()


# Удаляем user и записываем в журнал
def users_delete(name):
    user_cursor.execute("SELECT * FROM users WHERE name = ?", (name,))
    user_info = user_cursor.fetchall()
    user_cursor.execute("DELETE FROM users WHERE name = ?", (name,))
    journal_cursor.execute("INSERT INTO journal(type, user_id, name, password VALUES (?, ?, ?, ?)",
                           ("DELETE", user_info[0][0], user_info[0][1], user_info[0][2]))
    user_db.commit()
    journal_db.commit()


def create_users_table():
    user_cursor.execute("CREATE TABLE IF NOT EXISTS users(user_id INTEGER PRIMARY KEY, name TEXT UNIQUE, password TEXT)")


def create_journal_table():
    journal_cursor.execute("CREATE TABLE IF NOT EXISTS journal(type CHAR(6), user_id INTEGER, name TEXT, password TEXT)")


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
    create_users_table()

    journal_db, journal_cursor = connect_to_db('journal.db')
    if journal_db is None:
        clear('user', user_db, user_cursor)
        exit()
    create_journal_table()

    # Запускаем окно
    root.mainloop()

    # Запрос для себя
    user_cursor.execute("SELECT * FROM users")
    print(user_cursor.fetchall())

    journal_cursor.execute("SELECT * FROM journal")
    print(journal_cursor.fetchall())

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


"""
0) Добавить кнопки "Назад"
1) ПРОПИСАТЬ ВХОД
2) СДЕЛАТЬ ЗАМЕТКИ У ПОЛЬЗОВАТЕЛЕЙ
3) СДЕЛАТЬ ВОЗМОЖНОСТЬ СМЕНИТЬ ПАРОЛЬ
4) СДЕЛАТЬ ВОЗМОЖНОСТЬ УДАЛИТЬ УЧЁТНУЮ ЗАПИСЬ
5) В ОТДЕЛЬНОМ ПРОЕКТЕ ПОПРОБОВАТЬ СДЕЛАТЬ ЛИНК ДВУХ БД В ОДНУ
"""
