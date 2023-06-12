from django.urls import path
from API.views import *

urlpatterns = [
    path('employee-credentials', EmployeeCredentialsView.as_view()),
    path('admin-employees', AdminEmployeesView.as_view()),
    path('admin-employees/<int:employee_id>', AdminEmployeesView.as_view()),
    path('bugs', BugsView.as_view()),
    path('tester-bugs', TesterBugsView.as_view()),
    path('tester-bugs/<int:bug_id>', TesterBugsView.as_view()),
    path('programmer-bugs', ProgrammerBugsView.as_view()),
    path('programmer-bugs/<int:bug_id>', ProgrammerBugsView.as_view())
]
