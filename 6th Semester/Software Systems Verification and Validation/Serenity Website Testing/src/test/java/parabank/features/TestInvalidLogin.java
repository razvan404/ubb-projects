package parabank.features;


import net.serenitybdd.junit.runners.SerenityParameterizedRunner;
import net.thucydides.core.annotations.Managed;
import net.thucydides.core.annotations.Steps;
import net.thucydides.junit.annotations.UseTestDataFrom;
import org.junit.Before;
import org.junit.Test;
import org.junit.runner.RunWith;
import org.openqa.selenium.WebDriver;
import parabank.steps.EndUserSteps;

@RunWith(SerenityParameterizedRunner.class)
@UseTestDataFrom("src/test/resources/features/loginInvalidTestCase.csv")
public class TestInvalidLogin {
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
    public void loginWithInvalidCredentials() {
        user.isOnTheLoginPage();
        user.entersUsername(username);
        user.entersPassword(password);
        user.clicksLoginButton();
        user.shouldSeeErrorPage();
    }
}
