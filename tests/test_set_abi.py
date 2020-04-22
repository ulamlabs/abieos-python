import binascii

import abieos


def test_set_abi_json():
    with open('tests/test_abi.json', 'r') as f:
        abi = f.read()

    result = abieos.set_abi(abieos.string_to_name('test.abi'), abi)
    assert result


def test_set_abi_hex():
    contract = abieos.string_to_name('eosio.token')
    transfer_method = abieos.string_to_name('transfer')

    with open('tests/token_abi.hex', 'r') as f:
        abi = f.read()

    # before loading ABI, we shouldn't be able to check the type
    assert abieos.get_type_for_action(contract, transfer_method) is None

    # after loading ABI it will return "transfer"
    result = abieos.set_abi_hex(contract, abi)
    assert result
    assert abieos.get_type_for_action(contract, transfer_method) == 'transfer'


def test_set_abi_bin():
    contract = abieos.string_to_name('eosio.token')
    transfer_method = abieos.string_to_name('transfer')

    with open('tests/token_abi.hex', 'r') as f:
        abi = f.read()

    abi_bin = binascii.unhexlify(abi)

    # before loading ABI, we shouldn't be able to check the type
    assert abieos.get_type_for_action(contract, transfer_method) is None

    # after loading ABI it will return "transfer"
    result = abieos.set_abi_bin(contract, abi_bin, len(abi_bin))
    assert result
    assert abieos.get_type_for_action(contract, transfer_method) == 'transfer'
