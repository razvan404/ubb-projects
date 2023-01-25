class Song:
    def __init__(self, title, artist, type, publish_date):
        '''
        Initializam o melodie
        :param title: string
        :param artist: string
        :param type: string between "Rock" / "Pop" / "Jazz" / "Altele"
        :param publish_date: string in format 'dd.MM.yyyy'
        '''
        self.__title = str(title)
        self.__artist = str(artist)
        self.__type = type
        self.__publish_date = publish_date

    def get_title(self):
        '''
        Get the title of the music
        :return: string
        '''
        return self.__title

    def get_artist(self):
        '''
        Get the artist
        :return: string
        '''
        return self.__artist

    def get_type(self):
        '''
        Get the music type
        :return: string
        '''
        return self.__type

    def get_publish_date(self):
        '''
        Get the publish date
        :return: list of 3 elements (day, mounth, year)
        '''
        return self.__publish_date

    def validate(self):
        '''
        Validate if the song was entered corectly
        :return: ValueError if the song isn't valid
        '''
        errors = ''
        if self.__title == '':
            errors += ' | Titlul nu este specificat'
        if self.__artist == '':
            errors += ' | Artistul trebuie specificat'
        if self.__type not in ['Rock', 'Pop', 'Jazz', 'Altele']:
            errors += ' | Tipul melodiei este invalid'
        try:
            self.__publish_date = list([(token) for token in self.__publish_date.split('.')])
            if len(self.__publish_date) != 3: raise ValueError()
            if len(self.__publish_date[0]) != 2 or len(self.__publish_date[1]) != 2 \
                    or len(self.__publish_date[2]) != 4: raise ValueError()

            self.__publish_date[0] = int(self.__publish_date[0])
            self.__publish_date[1] = int(self.__publish_date[1])
            self.__publish_date[2] = int(self.__publish_date[2])

            if self.__publish_date[1] < 1 or self.__publish_date[1] > 12: raise ValueError()
            if self.__publish_date[1] in [1, 3, 5, 7, 8, 10, 12] and \
                    (self.__publish_date[0] > 31 or self.__publish_date[0] < 1): raise ValueError()
            if self.__publish_date[1] in [4, 6, 9, 11] and \
                        (self.__publish_date[0] > 30 or self.__publish_date[0] < 1): raise ValueError()
            if self.__publish_date[1] == 2 and \
                        (self.__publish_date[0] > 28 or self.__publish_date[0] < 1): raise ValueError()
        except ValueError or AttributeError:
            errors += ' | Data melodiei nu a fost introdusa corect.'
        if errors != '':
            raise ValueError(errors)


    def __eq__(self, other):
        '''
        Verifica daca 2 melodii sunt la fel
        :param other: song
        :return: True / False
        '''
        if self.__title == other.__title and self.__artist == other.__artist and \
            self.__type == other.__type and self.__publish_date == other.__publish_date:
            return True
        return False