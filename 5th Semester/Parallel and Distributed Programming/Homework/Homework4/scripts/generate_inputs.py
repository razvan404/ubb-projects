import os
import random


CONFIG = {
  "inputs_dir": "inputs/",
  "problem": {
    "countries": [
      "romania",
      "germany",
      "france",
      "italy",
      "spain",
    ],
    "participants_count": 100,
    "problems_count": 10,
    "banned_participants_count_per_country": 10,
    "max_score": 10,
  }
}


def generate_country_pairs(
  participants_count: int,
  problems_count: int,
  banned_participants_count_per_country: int,
  max_score: int,
  countries: list[str],
) -> dict[str, list[tuple[int, int]]]:
  last_idx = 0
  country_pairs = {country: [] for country in countries}
  for country in countries:
    participant_ids = range(last_idx, last_idx + participants_count)
    scores = {
      id: [random.randint(1, max_score) for _ in range(problems_count)]
      for id in participant_ids
    }
    banned_participants = random.sample(participant_ids, banned_participants_count_per_country)
    for id in banned_participants:
      scores[id][random.randint(problems_count * 2 // 3, problems_count - 1)] = -1
    country_pairs[country] = [(id, scores[id][score]) for score in range(problems_count) for id in participant_ids]
    last_idx += participants_count
  return country_pairs


def save_country_pairs(country_pairs: dict[str, list[tuple[int, int]]], input_dir: str):
  for country, pairs in country_pairs.items():
    with open(os.path.join(input_dir, country + ".txt"), "w") as f:
      for participant, score in pairs:
        f.write(f"{participant} {score}\n")


if __name__ == "__main__":
  country_pairs = generate_country_pairs(**CONFIG["problem"])
  save_country_pairs(country_pairs, CONFIG["inputs_dir"])
