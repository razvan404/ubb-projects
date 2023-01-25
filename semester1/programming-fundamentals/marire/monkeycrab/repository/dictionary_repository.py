from domain.word import Word, Translate

class Dictionary_Repository:
    def __init__(self, file):
        '''
        Se initializeaza cu numele fisierului
        :param file: string, file name
        '''
        self.__file = file

    def __load_from_file(self):
        '''
        Scoate din fisier traducerile
        :return: list of translates
        '''
        try:
            f = open(self.__file, 'r')
            translates = []
            lines = f.readlines()
            for line in lines:
                sword, slang, dword, dlang = [token.strip() for token in line.split(';')]
                source_word = Word(sword, slang).validate()
                destination_word = Word(dword, dlang).validate()
                translates.append(Translate(source_word, destination_word))
            f.close()
            return translates
        except ValueError or IOError:
            raise ValueError('Exista o problema la fisier!')

    def __save_to_file(self, translates):
        '''
        Salveaza in dictionar traducerile
        :param translates: list of translate
        :return:
        '''
        with open(self.__file, 'w') as f:
            for translate in translates:
                string = translate.get_source().get_word() + ';' + translate.get_source().get_lang() + ';' + \
                         translate.get_destination().get_word() + ';' + translate.get_destination().get_lang() + '\n'
                f.write(string)

    def translate_file(self, file, slang, export, dlang):
        '''
        Traduce textul dintr-un fisier dintr-o limba in alta
        :param file: string, import file name
        :param slang: string, source language
        :param export: string, export file name
        :param dlang: string, destination language
        :return: -
        '''
        try:
            f = open(file, 'r')
            f.close()
        except IOError:
            raise ValueError('Fisierul introdus nu exista!')
        f = open(file, 'r')
        g = open(export, 'w')
        translates = self.__load_from_file()
        lines = f.readlines()
        for line in lines:
            text = ''
            for word in line.split(' '):
                curent = Word(word, slang)
                modified = False
                for translate in translates:
                    if translate.get_source() == curent:
                        if translate.get_destination().get_lang() == dlang:
                            text += translate.get_destination().get_word() + ' '
                            modified = True
                            break
                        else:
                            for translate2 in translates:
                                if translate.get_destination() == translate2.get_source() and translate2.get_destination().get_lang() == dlang:
                                    text += translate2.get_destination().get_word() + ' '
                                    modified = True
                                    break
                                elif translate.get_destination() == translate2.get_destination() and translate2.get_source().get_lang() == dlang:
                                    text += translate2.get_source().get_word() + ' '
                                    modified = True
                                    break

                    elif translate.get_destination() == curent:
                        if translate.get_source().get_lang() == dlang:
                            text += translate.get_source().get_word() + ' '
                            modified = True
                            break
                        else:
                            for translate2 in translates:
                                if translate.get_source() == translate2.get_source() and translate2.get_destination().get_lang() == dlang:
                                    text += translate2.get_destination().get_word() + ' '
                                    modified = True
                                    break
                                elif translate.get_source() == translate2.get_destination() and translate2.get_source().get_lang() == dlang:
                                    text += translate2.get_source().get_word() + ' '
                                    modified = True
                                    break
                if modified is False:
                    text += '{' + word + '}' + ' '
            g.write(text)
        f.close()
        g.close()

    def store(self, translate):
        '''
        Pune in dictionar o noua traducere
        :param translate: translate
        :return: -
        '''
        translates = self.__load_from_file()
        if translate in translates:
            raise ValueError('Exista deja acelasi cuvant cu o traducere in limba specificata.')
        translates.append(translate)
        self.__save_to_file(translates)

    def get_lang_translates(self, lang):
        '''
        Returneaza toate traducerile cu o anumita limba
        :param lang: string, language
        :return: list of translates
        '''
        translates = self.__load_from_file()
        lang_translates = []
        for translate in translates:
            if translate.get_source().get_lang() == lang:
                lang_translates.append(translate)
        return lang_translates

    def clear(self):
        '''
        Sterge continutul dictionarului
        :return: -
        '''
        f = open(self.__file, 'w')
        f.close()

    def size(self):
        '''
        Returneaza dimensiunea dictionarului
        :return: size of dictionary
        '''
        translates = self.__load_from_file()
        return len(translates)
