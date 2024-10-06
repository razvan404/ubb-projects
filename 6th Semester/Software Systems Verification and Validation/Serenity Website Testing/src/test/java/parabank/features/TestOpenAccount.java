package parabank.features;


import net.serenitybdd.junit.runners.SerenityParameterizedRunner;
import net.serenitybdd.junit.runners.SerenityRunner;
import net.thucydides.core.annotations.Managed;
import net.thucydides.core.annotations.Steps;
import net.thucydides.junit.annotations.UseTestDataFrom;
import org.junit.Before;
import org.junit.Test;
import org.junit.runner.RunWith;
import org.openqa.selenium.WebDriver;
import parabank.steps.EndUserSteps;

@RunWith(SerenityParameterizedRunner.class)
@UseTestDataFrom("src/test/resources/features/openAccountTestCases.csv")
public class TestOpenAccount {
    @Steps
    EndUserSteps user;

    String username, password, accountType, existingAccount;

    @Managed(uniqueSession = true, driver = "firefox")
    public WebDriver webdriver;


    @Before
    public void setUp() {
        System.setProperty("webdriver.gecko.driver", ".\\drivers\\geckodriver.exe");
    }

    public void loginWithValidCredentials() {
        user.isOnTheLoginPage();
        user.entersUsername(username);
        user.entersPassword(password);
        user.clicksLoginButton();
        user.shouldSeeHomePage();
    }

    public void openNewAccount() {
        user.openNewAccountPage();
        user.selectsAccountType(accountType);
        user.selectsExistingAccount(existingAccount);

        user.clicksOpenNewAccountButton();
        user.shouldSeeAccountOpened();
    }

    public void checkOverviewTable() {
        user.clickOverviewButton();
        user.shouldOverviewTableHavePositiveNumberOfRows();
    }

    public void logout() {
        user.logsOut();
        user.shouldSeeLoginPage();
    }

    @Test
    public void openNewAccountAfterLogin() {
        loginWithValidCredentials();
        openNewAccount();
        checkOverviewTable();
        logout();
    }
}
