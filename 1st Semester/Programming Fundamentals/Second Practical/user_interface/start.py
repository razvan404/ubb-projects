from user_interface.menus import global_menu, error


class Interface:
    def __init__(self, repo, serv):
        self.__repo = repo
        self.__serv = serv

    def __store(self, sword, slang, dword, dlang):
        '''
        Adauga un cuvant in repository
        :param sword: source word, string
        :param slang: source language, string
        :param dword: destination word, string
        :param dlang: destination language, string
        :return: afiseaza confirmare daca s-a efectuat cu succes sau un mesaj corespunzator in caz contrar
        '''
        try:
            self.__serv.store(sword, slang, dword, dlang)
            print('Adaugarea a fost efectuata cu succes!')
        except ValueError as VE:
            print(VE)

    def __view_translates_by_language(self, lang):
        '''
        Afiseaza lista cu traducerile dupa o limba
        :param lang: limba corespunzatoare, string
        :return: print list of translates
        '''
        translates = self.__serv.view_translates_by_language(lang)
        for translate in translates:
            print('  Cuvant sursa:', translate.get_source().get_word(), '| Limba sursa:',
                  translate.get_source().get_lang(), '| Traducere:', translate.get_destination().get_word(),
                  '| Limba tradusa:', translate.get_destination().get_lang())

    def __translate_file(self, file, slang, export, dlang):
        '''
        Traduce un fisier dintr-o limba si exporteaza in alt fisier in alta limba
        :param file: file name, string
        :param slang: language, string
        :param export: file name, string
        :param dlang: language, string
        :return: modifica fisierul
        '''
        file = 'data/' + file
        export = 'data/' + export
        try:
            self.__serv.translate_file(file, slang, export, dlang)
            print('Traducerea s-a efectuat cu succes!')
        except ValueError as VE:
            print(VE)

    def begin(self):
        while True:

            option = input(global_menu())

            if option == '0':
                print('  La revedere!')
                break

            elif option == '1':
                sword = input('  Introdu cuvantul sursa: ')
                slang = input('  Introdu limba cuvantului sursa: ')
                dword = input('  Introdu cuvantul destinatie: ')
                dlang = input('  Introdu limba cuvantului destinatie: ')
                self.__store(sword, slang, dword, dlang)

            elif option == '2':
                lang = input('Introdu limba la care doresti sa vizualizezi traducerile: ')
                self.__view_translates_by_language(lang)

            elif option == '3':
                file = input('  Introdu fisierul sursa (trebuie sa se afle in data): ')
                slang = input('  Introdu limba textului: ')
                export = input('  Introdu fisierul destinatie (se va exporta in data): ')
                dlang = input('  Introdu limba in care vrei sa fie tradusa textul: ')
                self.__translate_file(file, slang, export, dlang)

            else:
                print(error())