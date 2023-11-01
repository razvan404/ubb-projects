import pandas as pd


class TableOfSymbols:
    def __init__(self, file_name: str):
        self._pandas_table = pd.read_csv(file_name, sep=',')

    def get_signification_to_symbol_dict(self):
        return self._pandas_table.groupby('Signification')['Symbol'].apply(list).to_dict()

    def get_symbol_to_code_dict(self):
        return self._pandas_table.set_index('Symbol')['Code'].to_dict()

    def get_symbols_list(self):
        return self._pandas_table['Symbol'].to_list()

    def to_markdown(self):
        return self._pandas_table.to_markdown()

    def as_pandas(self):
        return self._pandas_table
