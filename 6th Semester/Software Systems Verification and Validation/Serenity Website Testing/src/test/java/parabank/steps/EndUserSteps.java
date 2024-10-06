package parabank.steps;

import net.thucydides.core.annotations.Step;
import parabank.pages.LoginPage;
import parabank.pages.OpenAccountPage;

import static org.hamcrest.MatcherAssert.assertThat;
import static org.hamcrest.Matchers.hasItem;

public class EndUserSteps {

    LoginPage loginPage;
    OpenAccountPage openAccountPage;

    @Step
    public void isOnTheLoginPage() {
        loginPage.open();
    }

    @Step
    public void entersUsername(String username) {
        loginPage.enterUsername(username);
    }

    @Step
    public void entersPassword(String password) {
        loginPage.enterPassword(password);
    }

    @Step
    public void clicksLoginButton() {
        loginPage.clickLoginButton();
    }

    @Step
    public void shouldSeeHomePage() {
        assertThat("Home page should be displayed", loginPage.containsText("Accounts Overview"));
    }

    @Step
    public void shouldSeeLoginPage() {
        assertThat("The title of the page should be 'ParaBank | Welcome | Online Banking'", openAccountPage.getTitle().equals("ParaBank | Welcome | Online Banking"));
    }
    @Step
    public void shouldSeeErrorPage() {
        System.out.println(loginPage);
        assertThat("Error message should be displayed", loginPage.containsText("The username and password could not be verified.\n"));
    }

    @Step
    public void openNewAccountPage() {
        openAccountPage.open();
    }

    @Step
    public void selectsAccountType(String accountType) {
        openAccountPage.selectAccountType(accountType);
    }

    @Step
    public void selectsExistingAccount(String existingAccount) {
        openAccountPage.selectExistingAccount(existingAccount);
    }

    @Step
    public void clicksOpenNewAccountButton() {
        openAccountPage.clickOpenNewAccountButton();
    }

    @Step
    public void shouldSeeAccountOpened() {
        assertThat("Account opened message should be displayed", openAccountPage.isAccountOpened());
    }

    @Step
    public void clickOverviewButton() {
        openAccountPage.clickOverviewButton();
    }

    @Step
    public void shouldOverviewTableHavePositiveNumberOfRows() {
        assertThat(
                "Should have at least 1 row in the overview table",
                openAccountPage.selectNumberOfRowsOverviewTable() > 0
        );
    }

    @Step
    public void logsOut() {
        openAccountPage.clickLogoutButton();
    }
}