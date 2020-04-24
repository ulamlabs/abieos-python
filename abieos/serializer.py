import json

from abieos import private


class EosAbiSerializerException(Exception):
    """Serializer exception class"""


class EosAbiSerializer:
    """
    Convert data between JSON and binary format using ABIs

    :param loads: JSON decoder, defaults to ``json.loads``
    :param dumps: JSON encoder, defaults to ``json.dumps``
    """

    def __init__(self, *, loads=json.loads, dumps=json.dumps) -> None:
        self._context = private.create()
        self._loads = loads
        self._dumps = dumps

    def __del__(self) -> None:
        private.destroy(self._context)

    def _result_or_exception(self, result):
        if result is None:
            raise EosAbiSerializerException(private.get_error(self._context))
        return result

    def string_to_name(self, string: str) -> int:
        return self._result_or_exception(
            private.string_to_name(self._context, string)
        )

    def name_to_string(self, name: int) -> str:
        return self._result_or_exception(
            private.name_to_string(self._context, name)
        )

    def set_abi_from_json(self, contract: str, abi: dict) -> None:
        contract_name = self.string_to_name(contract)
        return self._result_or_exception(
            private.set_abi(self._context, contract_name, self._dumps(abi))
        )

    def set_abi_from_hex(self, contract: str, abi: str) -> None:
        contract_name = self.string_to_name(contract)
        return self._result_or_exception(
            private.set_abi_hex(self._context, contract_name, abi)
        )

    def set_abi_from_bin(self, contract: str, abi: bytes) -> None:
        contract_name = self.string_to_name(contract)
        return self._result_or_exception(
            private.set_abi_bin(self._context, contract_name, abi, len(abi))
        )

    def get_type_for_action(self, contract: str, action: str) -> str:
        contract_name = self.string_to_name(contract)
        action_name = self.string_to_name(action)
        return self._result_or_exception(
            private.get_type_for_action(
                self._context, contract_name, action_name
            )
        )

    def get_type_for_table(self, contract: str, table: str) -> str:
        contract_name = self.string_to_name(contract)
        table_name = self.string_to_name(table)
        return self._result_or_exception(
            private.get_type_for_table(
                self._context, contract_name, table_name
            )
        )

    def json_to_bin(self, contract: str, abi_type: str, data: dict) -> bytes:
        contract_name = self.string_to_name(contract)
        self._result_or_exception(
            private.json_to_bin(
                self._context, contract_name, abi_type, self._dumps(data)
            )
        )
        return self._result_or_exception(
            private.get_bin_data(self._context)
        )

    def json_to_hex(self, contract: str, abi_type: str, data: dict) -> str:
        contract_name = self.string_to_name(contract)
        self._result_or_exception(
            private.json_to_bin(
                self._context, contract_name, abi_type, self._dumps(data)
            )
        )
        return self._result_or_exception(
            private.get_bin_hex(self._context)
        )

    def bin_to_json(self, contract: str, abi_type: str, data: bytes) -> str:
        contract_name = self.string_to_name(contract)
        result = self._result_or_exception(
            private.bin_to_json(
                self._context, contract_name, abi_type, data, len(data)
            )
        )
        return self._loads(result)

    def hex_to_json(self, contract: str, abi_type: str, data: str) -> dict:
        contract_name = self.string_to_name(contract)
        result = self._result_or_exception(
            private.hex_to_json(self._context, contract_name, abi_type, data)
        )
        return self._loads(result)
