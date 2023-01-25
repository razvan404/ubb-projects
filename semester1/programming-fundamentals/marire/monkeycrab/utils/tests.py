from domain.word import Word
from utils.sorts import bubble

def test_bubble():
    a = [-1, -5, 3, 4, -2, 1]
    bubble(a, None)
    assert a == [-5, -2, -1, 1, 3, 4]
    a = [Word('caine', 'Ro'), Word('dog', 'En'), Word('curte', 'Ro')]
    bubble(a, 'word')
    assert a == [Word('caine', 'Ro'), Word('curte', 'Ro'), Word('dog', 'En')]