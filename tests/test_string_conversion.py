import abieos


def test_string_to_name():
    string = 'eosio.token'
    expected_name = 6138663591592764928
    assert abieos.string_to_name(string) == expected_name


def test_name_to_string():
    name = 6138663591592764928
    expected_string = 'eosio.token'
    assert abieos.name_to_string(name) == expected_string
