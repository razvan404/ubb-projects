from domain.word import Word, Translate
from utils.sorts import bubble

class Dictionary_Service():
    def __init__(self, repo):
        '''
        Initializam cu repo-ul asociat service-ului
        :param repo: dictionary repository
        '''
        self.__repo = repo

    def store(self, sword, slang, dword, dlang):
        '''
        Depoziteaza un nou cuvant in repository
        :param sword: string, word name
        :param slang: string, language name
        :param dword: string, word name
        :param dlang: string, language name
        :return:
        '''
        source_word = Word(sword, slang).validate()
        destination_word = Word(dword, dlang).validate()
        translate = Translate(source_word, destination_word).validate()
        self.__repo.store(translate)

    def view_translates_by_language(self, lang):
        '''
        Afiseaza cuvintele intr-o limba ordonate alfabetic
        :param lang: string, language
        :return: list of translate
        '''
        if lang not in ['Ro', 'En', 'Fr']:
            raise ValueError('Limba introdusa nu este valida!')
        translates = self.__repo.get_lang_translates(lang)
        bubble(translates, 'source word')
        return translates

    def translate_file(self, file, slang, export, dlang):
        '''
        Ia textul dintr-un fisier intr-o limba si exporteaza in alt fisier in alta limba
        :param file: string, file name
        :param slang: string, language name
        :param export: string, file name
        :param dlang: string, language name
        :return: -
        :raises: ValueError in caz ca limba nu este valida.
        '''
        text = ''
        if slang not in ['Ro', 'En', 'Fr']:
            text += 'Limba sursa nu este valida! '
        if dlang not in ['Ro', 'En', 'Fr']:
            text += 'Limba destinatie nu este valida!'
        if text != '':
            raise ValueError(text)
        self.__repo.translate_file(file, slang, export, dlang)