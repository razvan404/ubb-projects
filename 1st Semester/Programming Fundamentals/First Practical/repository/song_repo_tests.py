from domain.song import Song
from repository.song_repository import SongRepoFile

def test_load_from_file():
    good_repo = SongRepoFile('test_data.txt')
    non_existent_repo = SongRepoFile('test_atad.txt')
    bad_repo = SongRepoFile('bad_data.txt')
    try:
        test_songs = good_repo.load_from_file()
        assert True
    except IOError:
        assert False
    try:
        non_existent_repo.load_from_file()
        assert False
    except IOError:
        assert True
    try:
        bad_repo.load_from_file()
        assert False
    except IOError:
        assert True

    assert test_songs[0].get_publish_date() == [22, 1, 2022]
    assert test_songs[1].get_type() == 'Jazz'

def test_save_to_file():
    good_repo = SongRepoFile('test_data.txt')
    test_songs = good_repo.load_from_file()
    initial_size = len(test_songs)
    s = Song('Martin Jones', 'Alabama', 'Jazz', '22.01.2022')
    s.validate()
    test_songs.append(s)
    good_repo.save_to_file(test_songs)
    test_songs = good_repo.load_from_file()
    assert len(test_songs) - initial_size == 1

def test_export():
    good_repo = SongRepoFile('test_data.txt')
    test_songs = good_repo.load_from_file()
    s = Song('Martin Jones', 'Alabama', 'Jazz', '22.01.2022')
    s.validate()
    test_songs.append(s)
    good_repo.export('test_export.txt', test_songs)
    try:
        f = open('test_data.txt', 'r')
        assert True
    except IOError:
        assert False

def test_add_song_to_file():
    good_repo = SongRepoFile('test_data.txt')
    test_songs = good_repo.load_from_file()
    initial_size = len(test_songs)
    good_repo.add_song_to_file(Song('Martinus Jonny', 'Balamuc', 'Pop', '20.01.2022'))
    test_songs = good_repo.load_from_file()
    assert len(test_songs) == initial_size + 1
    try:
        good_repo.add_song_to_file(Song('Martinus Jonny', 'Balamuc', 'Manele', '20.01.2022'))
        assert False
    except ValueError:
        assert True

def run_tests():
    test_load_from_file()
    test_save_to_file()
    test_export()
    test_add_song_to_file()

run_tests()