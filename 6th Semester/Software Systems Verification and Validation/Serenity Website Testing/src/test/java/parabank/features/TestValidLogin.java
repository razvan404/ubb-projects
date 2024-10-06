package parabank.features;


import net.serenitybdd.junit.runners.SerenityParameterizedRunner;
import net.thucydides.core.annotations.Managed;
import net.thucydides.core.annotations.Steps;
import net.thucydides.junit.annotations.UseTestDataFrom;
import parabank.steps.EndUserSteps;
import org.junit.Before;
import org.junit.Test;
import org.junit.runner.RunWith;
import org.openqa.selenium.WebDriver;

@RunWith(SerenityParameterizedRunner.class)
@UseTestDataFrom("src/test/resources/features/loginValidTestCase.csv")
public class TestValidLogin {
    @Steps
    EndUserSteps user;

    String username, password;

    @Managed(uniqueSession = true, driver = "firefox")
    public WebDriver webdriver;

    @Before
    public void setUp() {
        System.setProperty("webdriver.gecko.driver", ".\\drivers\\geckodriver.exe");
    }

    @Test
    public void loginWithValidCredentials() {
        System.out.println(username + " "  +password);
        user.isOnTheLoginPage();
        user.entersUsername(username);
        user.entersPassword(password);
        user.clicksLoginButton();
        user.shouldSeeHomePage();
    }
}
