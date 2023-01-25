from user_interface.start import Interface
from service.dictionary_service import Dictionary_Service
from repository.dictionary_repository import Dictionary_Repository

if __name__ == '__main__':
    repo = Dictionary_Repository('data/dictionary')
    serv = Dictionary_Service(repo)
    prog = Interface(repo, serv)
    prog.begin()
