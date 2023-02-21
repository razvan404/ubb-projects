from domain.song import Song

def test_validate_song():
    try:
        s = Song('Armin', 'Solemio', 'Manele', '22.01.2022')
        s.validate()
        assert False
    except ValueError:
        assert True
    try:
        s = Song('Armin', 'Solemio', 'Altele', '22.01.2022')
        s.validate()
        assert True
    except ValueError:
        assert False
    try:
        s = Song('Armin', 'Solemio', 'Rock', '24.13.2021')
        s.validate()
        assert False
    except ValueError:
        assert True
    try:
        s = Song('Armin', 'Solemio', 'Rock', '5.07.2021')
        s.validate()
        assert False
    except ValueError:
        assert True
    try:
        s = Song('Armin', 'Solemio', 'Rock', '30.02.2021')
        s.validate()
        assert False
    except ValueError:
        assert True
    try:
        s = Song('Armin', 'Solemio', 'Rock', '22.01.202')
        s.validate()
        assert False
    except ValueError:
        assert True
    try:
        s = Song('Armin', 'Solemio', 'Rock', '22.01.2022')
        s.validate()
        assert True
    except ValueError:
        assert False

def run_tests():
    test_validate_song()

run_tests()