import binascii

import pytest

from abieos import EosAbiSerializerException


def test_set_abi_json(serializer):
    with open('tests/test_abi.json', 'r') as f:
        abi = f.read()

    abi = serializer._loads(abi)
    serializer.set_abi_from_json('test.abi', abi)


def test_set_abi_from_hex(serializer):
    with open('tests/token_abi.hex', 'r') as f:
        abi = f.read()

    # before loading ABI, we shouldn't be able to check the type
    with pytest.raises(EosAbiSerializerException):
        serializer.get_type_for_action('eosio.token', 'transfer')

    # after loading ABI it will return "transfer"
    serializer.set_abi_from_hex('eosio.token', abi)
    assert (
        serializer.get_type_for_action('eosio.token', 'transfer') == 'transfer'
    )


def test_set_abi_bin(serializer):
    with open('tests/token_abi.hex', 'r') as f:
        abi = f.read()

    abi_bin = binascii.unhexlify(abi)

    # before loading ABI, we shouldn't be able to check the type
    with pytest.raises(EosAbiSerializerException):
        serializer.get_type_for_action('eosio.token', 'transfer')

    # after loading ABI it will return "transfer"
    serializer.set_abi_from_bin('eosio.token', abi_bin)
    assert (
        serializer.get_type_for_action('eosio.token', 'transfer') == 'transfer'
    )
