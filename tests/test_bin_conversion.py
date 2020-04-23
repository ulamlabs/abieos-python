import json

import pytest


@pytest.fixture
def eosio_token(serializer):
    with open('tests/token_abi.hex', 'r') as f:
        abi = f.read()
    serializer.set_abi_from_hex('eosio.token', abi)


@pytest.fixture
def example_json():
    return {
        'from': 'useraaaaaaaa',
        'to': 'useraaaaaaab',
        'quantity': '0.0001 SYS',
        'memo': '',
    }


@pytest.fixture
def example_bin():
    return (
        b'`\x8c1\xc6\x18s\x15\xd6p\x8c1\xc6\x18s\x15\xd6\x01\x00\x00\x00\x00'
        b'\x00\x00\x00\x04SYS\x00\x00\x00\x00\x00'
    )


@pytest.fixture
def example_hex():
    return '608C31C6187315D6708C31C6187315D60100000000000000045359530000000000'


def test_json_to_bin(eosio_token, serializer, example_json, example_bin):
    transfer = serializer.get_type_for_action('eosio.token', 'transfer')
    result = serializer.json_to_bin(
        'eosio.token', transfer, json.dumps(example_json)
    )
    assert result == example_bin


def test_json_to_hex(eosio_token, serializer, example_json, example_hex):
    transfer = serializer.get_type_for_action('eosio.token', 'transfer')
    result = serializer.json_to_hex(
        'eosio.token', transfer, json.dumps(example_json)
    )
    assert result == example_hex


def test_bin_to_json(eosio_token, serializer, example_bin, example_json):
    transfer = serializer.get_type_for_action('eosio.token', 'transfer')
    result = serializer.bin_to_json('eosio.token', transfer, example_bin)
    assert result is not None
    assert json.loads(result) == example_json


def test_hex_to_json(eosio_token, serializer, example_hex, example_json):
    transfer = serializer.get_type_for_action('eosio.token', 'transfer')
    result = serializer.hex_to_json('eosio.token', transfer, example_hex)
    assert result is not None
    assert json.loads(result) == example_json
