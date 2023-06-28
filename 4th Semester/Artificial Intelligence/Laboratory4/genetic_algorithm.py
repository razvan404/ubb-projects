from random import uniform, choice
from typing import Set, Generic, TypeVar, List

from my_chromosome import AbstractChromosome
from my_graph import MyGraph


T = TypeVar('T', bound=AbstractChromosome)


class GeneticAlgorithm(Generic[T]):
    def __init__(self, graph: MyGraph, constructor: callable, algorithm: str,
                 population_size: int, population_type: str, mutate_prob: int = 0.2):
        self.__population_type = population_type
        self.__graph = graph
        self.__cached_fitness = {}
        if population_type == 'set':
            self.__population = set()
        elif population_type == 'list':
            self.__population = []
        else:
            raise ValueError('Invalid population type!')
        self.__algorithm = algorithm
        while len(self.__population) < population_size:
            if population_type == 'set':
                self.__population.add(self.apply_fitness(constructor(graph)))
            else:
                self.__population.append(self.apply_fitness(constructor(graph)))
        self.__population_size = population_size
        self.__mutate_prob = mutate_prob

    @property
    def population(self):
        return self.__population

    def apply_fitness(self, chromosome: T) -> T:
        if chromosome not in self.__cached_fitness:
            chromosome.fitness = self.__calculate_fitness(chromosome)
            self.__cached_fitness[chromosome] = chromosome.fitness
        else:
            chromosome.fitness = self.__cached_fitness[chromosome]
        return chromosome

    def __select(self, population=None) -> T:
        if population is None:
            population = self.__population
        chromosome1 = choice(tuple(population))
        chromosome2 = choice(tuple(population))

        return chromosome1 if self.__cached_fitness[chromosome1] < self.__cached_fitness[chromosome2] else chromosome2

    def __calculate_fitness(self, chromosome: T) -> int:
        path_cost = 0
        for i in range(len(chromosome.path) - 1):
            if self.__graph.adjacency_matrix[chromosome.path[i]][chromosome.path[i + 1]] == 0:
                path_cost += 10000
            else:
                path_cost += self.__graph.adjacency_matrix[chromosome.path[i]][chromosome.path[i + 1]]
        if self.__algorithm == 'TSP':
            if self.__graph.adjacency_matrix[chromosome.path[-1]][chromosome.path[0]] == 0:
                path_cost += 10000
            else:
                path_cost += self.__graph.adjacency_matrix[chromosome.path[-1]][chromosome.path[0]]
        return path_cost

    def best_chromosomes(self) -> List[T]:
        population = list(self.__population)
        chromosomes = [population[0]]
        best_fitness = population[0].fitness
        if self.__population_type == 'set':
            for i in range(1, self.__population_size):
                if population[i].fitness < best_fitness:
                    chromosomes = [population[i]]
                    best_fitness = population[i].fitness
                elif population[i].fitness == best_fitness:
                    chromosomes.append(population[i])
        else:
            for i in range(1, self.__population_size):
                if population[i].fitness < best_fitness:
                    chromosomes = [population[i]]
                    best_fitness = population[i].fitness
                elif population[i].fitness == best_fitness and population[i] not in chromosomes:
                    chromosomes.append(population[i])
        return chromosomes

    def next_generation(self):
        # Select top 10% chromosomes
        if self.__population_type == 'set':
            new_population = set(sorted(self.__population, reverse=False)[:self.__population_size // 10])
        else:
            new_population = sorted(self.__population, reverse=False)[:self.__population_size // 10]

        # Generate offsprings from top individuals
        for _ in range(self.__population_size // 8):
            child1, child2 = None, None
            while child1 is None:
                parent1 = self.__select(new_population)
                parent2 = self.__select(new_population)
                child1, child2 = parent1.crossover(parent2)
            if self.__population_type == 'set':
                new_population.add(self.apply_fitness(child1.mutate() if uniform(0, 1) < self.__mutate_prob
                                                      else child1))
                new_population.add(self.apply_fitness(child2.mutate() if uniform(0, 1) < self.__mutate_prob
                                                      else child2))
            else:
                new_population.append(self.apply_fitness(child1.mutate() if uniform(0, 1) < self.__mutate_prob
                                                         else child1))
                new_population.append(self.apply_fitness(child2.mutate() if uniform(0, 1) < self.__mutate_prob
                                                         else child2))

        # Generate some offsprings from the rest of the individuals
        for _ in range(len(new_population), self.__population_size * 19 // 50):
            child1, child2 = None, None
            while child1 is None:
                parent1 = self.__select()
                parent2 = self.__select()
                child1, child2 = parent1.crossover(parent2)
            if self.__population_type == 'list':
                new_population.append(self.apply_fitness(child1.mutate() if uniform(0, 1) < self.__mutate_prob
                                                         else child1))
                new_population.append(self.apply_fitness(child2.mutate() if uniform(0, 1) < self.__mutate_prob
                                                         else child2))
            else:
                new_population.add(self.apply_fitness(child1.mutate() if uniform(0, 1) < self.__mutate_prob
                                                      else child1))
                new_population.add(self.apply_fitness(child2.mutate() if uniform(0, 1) < self.__mutate_prob
                                                      else child2))

        # Fill remaining slots with random individuals
        while len(new_population) < self.__population_size:
            if self.__population_type == 'set':
                new_population.add(self.__select())
            else:
                new_population.append(self.__select())

        self.__population = new_population
