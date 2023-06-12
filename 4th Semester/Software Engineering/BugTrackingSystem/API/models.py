from API.managers import *


class Employee(models.Model):
    username = models.CharField(max_length=24, unique=True, null=False)
    password = models.CharField(max_length=24, null=False)
    type = models.CharField(max_length=16)


class EmployeeSession(models.Model):
    employee = models.ForeignKey(Employee, on_delete=models.CASCADE)
    session = models.CharField(max_length=15, unique=True, null=False)
    created_at = models.DateTimeField(auto_now_add=True)


class Administrator(Employee):
    objects = AdministratorManager()

    class Meta:
        proxy = True


class Tester(Employee):
    objects = TesterManager()

    class Meta:
        proxy = True


class Programmer(Employee):
    objects = ProgrammerManager()

    class Meta:
        proxy = True


class Bug(models.Model):
    title = models.CharField(max_length=32, null=False)
    description = models.CharField(max_length=256, null=False)
    status = models.CharField(max_length=10, null=False, default='unassigned')
    created_at = models.DateTimeField(auto_now_add=True)
    reporter = models.ForeignKey(Tester, on_delete=models.SET_NULL, null=True,
                                 related_name='reported_bugs')
    assigned_to = models.ForeignKey(Programmer, on_delete=models.SET_NULL, null=True,
                                    related_name='bugs_to_solve', default=None)
    solved_by = models.ForeignKey(Programmer, on_delete=models.SET_NULL, null=True,
                                  related_name='solved_bugs', default=None)
