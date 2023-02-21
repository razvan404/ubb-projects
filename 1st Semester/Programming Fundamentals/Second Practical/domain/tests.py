from domain.word import Word, Translate

def test_word():
    try:
        a = Word('Mexic', 'Sp')
        a.validate()
        assert False
    except ValueError:
        assert True

    try:
        a = Word('', 'Ro')
        a.validate()
        assert False
    except ValueError:
        assert True

    a = Word('mancare', 'En')
    assert a.validate() == a
    assert a.get_word() == 'mancare'
    assert a.get_lang() == 'En'

def test_transl():
    a = Word('mancare', 'Ro')
    b = Word('food', 'En')
    c = Translate(a, b)
    assert c.get_destination().get_lang() == 'En'
    assert c.get_source().get_word() == 'mancare'
    d = Word('mancarica', 'Ro')
    try:
        Translate(a, d).validate()
        assert False
    except ValueError:
        assert True