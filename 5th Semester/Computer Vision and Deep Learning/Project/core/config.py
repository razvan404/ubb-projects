import yaml


def load_config(section: str):
    with open("config.yaml", "rt") as file:
        return yaml.safe_load(file.read())[section]
