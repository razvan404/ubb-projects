from domain.song import Song

class SongRepoFile:
    def __init__(self, file_name):
        self.__file = file_name

    def load_from_file(self):
        '''
        Load songs from the file
        :return: list of songs
        '''
        try:
            f = open(self.__file, 'r')
            lines = f.readlines()
            songs = []

            for line in lines:
                title, artist, type, publish_date = [token.strip() for token in line.split(';')]

                new_song = Song(title, artist, type, publish_date)
                new_song.validate()
                songs.append(new_song)
            f.close()
            return songs
        except ValueError or IOError as error:
            raise IOError(error)


    def save_to_file(self, songs):
        '''
        Save to repository's file the new song list
        :param songs: list of songs
        :return: -
        '''
        with open(self.__file, 'w') as f:
            for song in songs:
                d = ''
                m = ''
                if len(str(song.get_publish_date()[0])) == 1:
                    d = '0'
                if len(str(song.get_publish_date()[1])) == 1:
                    m = '0'
                song_string = str(song.get_title()) + ';' + str(song.get_artist()) + ';' + str(song.get_type())\
                              + ';' + d + str(song.get_publish_date()[0]) + '.' + m + str(song.get_publish_date()[1]) + '.'\
                              + str(song.get_publish_date()[2]) + '\n'
                f.write(song_string)

    def export(self, export_file, songs):
        '''
        Save to repository's file the new song list
        :param songs: list of songs
        :param export_file: name of the file
        :return: -
        '''
        with open(export_file, 'w') as f:
            for song in songs:
                d = ''
                m = ''
                if len(str(song.get_publish_date()[0])) == 1:
                    d = '0'
                if len(str(song.get_publish_date()[1])) == 1:
                    m = '0'
                song_string = str(song.get_artist()) + ';' + str(song.get_title()) + ';' + d + \
                              str(song.get_publish_date()[0]) + '.' + m + str(song.get_publish_date()[1]) \
                              + '.' + str(song.get_publish_date()[2]) + ';' + str(song.get_type()) + '\n'
                f.write(song_string)

    def add_song_to_file(self, new_song):
        '''
        Add a new song to the song list
        :param new_song: valitaded song
        :return: -
        '''
        songs = self.load_from_file()
        songs.append(new_song)
        self.save_to_file(songs)

    def find_song(self, wanted_song):
        '''
        Find a song in the song list and returns the index
        where the song is in the songs list
        :param wanted_song: valid song
        :return: index or -1 if the song is not in the list
        '''
        songs = self.load_from_file()
        index = 0
        while index < len(songs) and wanted_song != songs[index]:
            index += 1
        if index == len(songs):
            return -1
        return index

    def modify_song(self, wanted_songs, new_type, new_date):
        '''
        Modify the type and the date of an existing song
        :param wanted_songs: valid song
        :param new_type: string
        :param new_date: string
        :return: modify from the file the song
        '''
        songs = self.load_from_file()
        index = self.find_song(wanted_songs)
        if index == -1:
            raise ValueError('Acea melodie nu exista in fisier!')
        modified_song = Song(songs[index].get_title(), songs[index].get_artist(), new_type, new_date)
        modified_song.validate()
        songs[index] = modified_song
        self.save_to_file(songs)

    def get_all_songs(self):
        '''
        Returns the list of the songs
        :return: list of songs
        '''
        songs = self.load_from_file()
        return songs
