def test_string_to_name(serializer):
    string = 'eosio.token'
    expected_name = 6138663591592764928
    assert serializer.string_to_name(string) == expected_name


def test_name_to_string(serializer):
    name = 6138663591592764928
    expected_string = 'eosio.token'
    assert serializer.name_to_string(name) == expected_string
