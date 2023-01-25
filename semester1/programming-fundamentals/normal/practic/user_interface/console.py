from domain.song import Song
from user_interface.menus import global_menu, invalid

class Console:
    def __init__(self, serv):
        self.serv = serv

    def modify_song(self):
        title = input('Introdu titlul melodiei ce doresti sa fie modificate: ')
        artist = input('Introdu artistul melodiei ce doresti sa fie modificate: ')
        type = input('Introdu tipul melodiei ce doresti sa fie modificate: ')
        publish_date = input('Introdu data melodiei ce doresti sa fie modificate (dd.yy.mmmm): ')
        wanted_song = Song(title, artist, type, publish_date)
        try:
            wanted_song.validate()
        except ValueError as ve:
            print(ve)
            return -1
        new_type = input('Introdu noul tip al melodiei selectate: ')
        new_date = input('Introdu noua data pentru melodia selectata: ')
        try:
            self.serv.modify_song(wanted_song, new_type, new_date)
        except ValueError as ve:
            print(ve)
            return -1
        print("Modificarea a fost efectuata cu succes!\n")

    def random_songs(self):
        number_of_songs = int(input('Introdu numarul de melodii ce doresti sa fie generate aleatoriu: '))
        titles = input('Introdu lista de titluri separate prin virgula: ')
        artists = input('Introdu lista de artisti separati prin virgula: ')
        self.serv.add_random_songs(number_of_songs, titles, artists)
        print('Au fost adaugate', number_of_songs, 'melodii cu succes')

    def export(self):
        export_file = input('Introdu numele fisierului (fara extensia .txt): ')
        export_file += '.txt'
        self.serv.export(export_file)

    def start(self):
        while True:
            option = input(global_menu())

            if option == '0':
                print(' La revedere!')
                break

            elif option == '1':
                self.modify_song()

            elif option == '2':
                self.random_songs()

            elif option == '3':
                self.export()

            else:
                invalid()

#L,M,N,RR,KQ ASD,ART,KPR,ADR,NPR