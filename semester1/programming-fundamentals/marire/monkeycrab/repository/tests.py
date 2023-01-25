from domain.word import Word, Translate
from repository.dictionary_repository import Dictionary_Repository

def test_store():
    repo = Dictionary_Repository('data_test/test')
    trans = Translate(Word('mancare', 'Ro').validate(), Word('food', 'En').validate())
    repo.store(trans)
    assert repo.size() == 1
    try:
        trans = Translate(Word('mancare', 'Ro').validate(), Word('malanga', 'En').validate())
        repo.store(trans)
        assert False
    except ValueError:
        assert True
    repo.clear()
    assert repo.size() == 0

def test_size():
    repo = Dictionary_Repository('data_test/test')
    trans = Translate(Word('mancare', 'Ro').validate(), Word('food', 'En').validate())
    repo.store(trans)
    assert repo.size() == 1
    trans = Translate(Word('mancar', 'Ro').validate(), Word('foo', 'En').validate())
    repo.store(trans)
    trans = Translate(Word('manca', 'Ro').validate(), Word('fo', 'En').validate())
    repo.store(trans)
    assert repo.size() == 3
    repo.clear()
    assert repo.size() == 0

def test_translate():
    repo = Dictionary_Repository('data_test/test')
    trans = Translate(Word('Ana', 'Ro'), Word('Ana', 'En'))
    repo.store(trans)
    trans = Translate(Word('mere', 'Ro'), Word('merre', 'Fr'))
    repo.store(trans)
    trans = Translate(Word('apples', 'En'), Word('merre', 'Fr'))
    repo.store(trans)
    repo.translate_file('data_test/import', 'Ro', 'data_test/export', 'En')
    repo.clear()
    f = open('data_test/export', 'r')
    line = f.readline()
    assert line == 'Ana {are} apples '

def test_get_lang_translate():
    repo = Dictionary_Repository('data_test/test')
    trans = Translate(Word('Ana', 'Ro'), Word('Ana', 'En'))
    repo.store(trans)
    trans = Translate(Word('mere', 'Ro'), Word('apples', 'En'))
    repo.store(trans)
    trans = Translate(Word('caine', 'Ro'), Word('dog', 'En'))
    repo.store(trans)
    trans = Translate(Word('dog', 'En'), Word('caine', 'Ro'))
    repo.store(trans)
    transl = repo.get_lang_translates('Ro')
    assert len(transl) == 3
    assert transl[2].get_source().get_word() == 'caine'
    repo.clear()
    