import json

import pytest

import abieos


@pytest.fixture
def eosio_token():
    contract = abieos.string_to_name('eosio.token')
    with open('tests/token_abi.hex', 'r') as f:
        abi = f.read()
    abieos.set_abi_hex(contract, abi)
    return contract


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


@pytest.fixture
def transfer(eosio_token):
    return abieos.get_type_for_action(
        eosio_token, abieos.string_to_name('transfer')
    )


def test_json_to_bin(eosio_token, transfer, example_json, example_bin):
    result = abieos.json_to_bin(
        eosio_token, transfer, json.dumps(example_json)
    )
    assert result

    binary = abieos.get_bin_data()
    assert binary == example_bin
    assert abieos.get_bin_size() == len(binary)


def test_json_to_hex(eosio_token, transfer, example_json, example_hex):
    result = abieos.json_to_bin(
        eosio_token, transfer, json.dumps(example_json)
    )
    assert result

    hex_data = abieos.get_bin_hex()
    assert hex_data == example_hex
    assert abieos.get_bin_size() == len(hex_data) / 2


def test_bin_to_json(eosio_token, transfer, example_bin, example_json):
    result = abieos.bin_to_json(
        eosio_token, transfer, example_bin, len(example_bin)
    )
    assert result is not None
    assert json.loads(result) == example_json


def test_hex_to_json(eosio_token, transfer, example_hex, example_json):
    result = abieos.hex_to_json(eosio_token, transfer, example_hex)
    assert result is not None
    assert json.loads(result) == example_json
