from service.dictionary_service import Dictionary_Service
from repository.dictionary_repository import Dictionary_Repository

def test_store():
    repo = Dictionary_Repository('data_test/test')
    serv = Dictionary_Service(repo)
    serv.store('mancare', 'Ro', 'food', 'En')
    assert repo.size() == 1
    try:
        serv.store('mancare', 'Ro', 'malanga', 'En')
        assert False
    except ValueError:
        assert True
    repo.clear()
    assert repo.size() == 0

def test_translates_by_language():
    repo = Dictionary_Repository('data_test/test')
    serv = Dictionary_Service(repo)
    serv.store('Ana', 'Ro', 'Ana', 'En')
    serv.store('mere', 'Ro', 'apples', 'En')
    serv.store('caine', 'Ro', 'dog', 'En')
    serv.store('dog', 'En', 'caine', 'Ro')
    transl = serv.view_translates_by_language('Ro')
    assert len(transl) == 3
    assert transl[2].get_source().get_word() == 'mere'
    repo.clear()

def test_translate():
    repo = Dictionary_Repository('data_test/test')
    serv = Dictionary_Service(repo)
    serv.store('Ana', 'Ro', 'Ana', 'En')
    serv.store('mere', 'Ro', 'merre', 'Fr')
    serv.store('apples', 'En', 'merre', 'Fr')
    serv.translate_file('data_test/import', 'Ro', 'data_test/export', 'En')
    repo.clear()
    f = open('data_test/export', 'r')
    line = f.readline()
    assert line == 'Ana {are} apples {galbene} '