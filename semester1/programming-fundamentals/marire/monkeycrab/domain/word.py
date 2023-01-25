class Word:
    def __init__(self, word, lang):
        '''
        Initializam un cuvant
        :param word: string
        :param lang: string
        '''
        self.__word = word
        self.__lang = lang

    def get_word(self):
        '''
        Returneaza cuvantul
        :return: string
        '''
        return self.__word

    def get_lang(self):
        '''
        Returneaza limba
        :return: string
        '''
        return self.__lang

    def validate(self):
        '''
        Verificam daca cuvantul este introdus in format curent
        :return: string
        '''
        errors = ''
        if self.__lang not in ['En', 'Ro', 'Fr']:
            errors += 'Limba introdusa nu este una valida! '
        if self.__word == '':
            errors += 'Cuvantul nu trebuie sa fie vid! '
        if errors != '':
            raise ValueError(errors)
        return self

    def __eq__(self, other):
        '''
        Verifica daca 2 cuvinte au aceeasi forma si limba
        :param other:
        :return:
        '''
        if self.__word == other.__word and self.__lang == other.__lang:
            return True
        return False


class Translate:
    def __init__(self, source, destination):
        '''
        Retinem o traducere
        :param source: word
        :param destination: word
        '''
        self.__source = source
        self.__destination = destination

    def get_source(self):
        '''
        Returneaza cuvantul sursa
        :return: word
        '''
        return self.__source

    def get_destination(self):
        '''
        Returneaza cuvantul destinatie
        :return: word
        '''
        return self.__destination

    def validate(self):
        '''
        Valideaza daca o traducere este corecta
        :return: word
        '''
        if self.__source.get_lang() == self.__destination.get_lang():
            raise ValueError('Limbile trebuie sa fie diferite!')
        return self

    def __eq__(self, other):
        '''
        Verifica daca o traducere are acelasi cuvant sursa ca alta si aceeasi limba in care este tradus
        :param other: translate
        :return: True / False
        '''
        if self.__source == other.__source and self.__destination.get_lang() == other.__destination.get_lang():
            return True
        return False
