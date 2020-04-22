import pytest

import abieos


@pytest.fixture(autouse=True)
def context():
    abieos.create()
