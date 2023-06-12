from django.db import models


class AdministratorManager(models.Manager):
    def get_queryset(self):
        return super(AdministratorManager, self).get_queryset().filter(type='administrator')

    def create(self, **kwargs):
        kwargs.update({'type': 'admin'})
        return super(AdministratorManager, self).create(**kwargs)


class TesterManager(models.Manager):
    def get_queryset(self):
        return super(TesterManager, self).get_queryset().filter(type='tester')

    def create(self, **kwargs):
        kwargs.update({'type': 'tester'})
        return super(TesterManager, self).create(**kwargs)


class ProgrammerManager(models.Manager):
    def get_queryset(self):
        return super(ProgrammerManager, self).get_queryset().filter(type='programmer')

    def create(self, **kwargs):
        kwargs.update({'type': 'programmer'})
        return super(ProgrammerManager, self).create(**kwargs)
