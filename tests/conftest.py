import pytest

from abieos import EosAbiSerializer


@pytest.fixture
def serializer():
    return EosAbiSerializer()
