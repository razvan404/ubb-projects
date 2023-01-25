from repository.song_repository import SongRepoFile
from domain.song import Song
from utils.sort import bubble
import random


class SongServ():
    def __init__(self, repo):
        self.repo = repo

    def modify_song(self, wanted_song, new_type, new_date):
        '''
        Replace the type and the date of the wanted song if it is in the repo's file
        :param wanted_song: song
        :param new_type: string
        :param new_date: string
        :return: modify the repo file
        '''
        self.repo.modify_song(wanted_song, new_type, new_date)

    def export(self, file):
        '''
        Export the ordered songs.
        :param file: the name of the file
        :return: to the given file
        '''
        songs = self.repo.get_all_songs()
        bubble(songs, 'date')
        self.repo.export(file, songs)

    def add_random_songs(self, number_of_songs, titles, artists):
        '''
        Adauga melodii random in fisier
        :param number_of_songs: int
        :param titles: string
        :param artists: string
        :return: -
        '''
        for i in range(0, number_of_songs):
            try:
                day = random.randint(10, 28)
                month = random.randint(1, 12)
                year = random.randint(1750, 2022)
                day = str(day)
                if month < 10:
                    month = '0' + str(month)
                else:
                    month = str(month)
                year = str(year)
                date = day + '.' + month + '.' + year
                type = random.choice(['Rock', 'Pop', 'Jazz', 'Altele'])
                title = random.choice([token.strip() for token in titles.split(',')])
                artist = random.choice([token.strip() for token in artists.split(',')])
                print(title, artist, type, date)
                random_song = Song(title, artist, type, date)
                random_song.validate()
                self.repo.add_song_to_file(random_song)

            except ValueError:
                i -= 1
