package parabank.pages;

import net.thucydides.core.annotations.DefaultUrl;
import net.serenitybdd.core.pages.WebElementFacade;

import net.serenitybdd.core.annotations.findby.FindBy;

import net.thucydides.core.pages.PageObject;

@DefaultUrl("https://parabank.parasoft.com/parabank/index.htm?ConnType=JDBC")
public class LoginPage extends PageObject {
    @FindBy(name="username")
    private WebElementFacade usernameField;

    @FindBy(name="password")
    private WebElementFacade passwordField;

    @FindBy(css = ".button[value='Log In']")
    private WebElementFacade loginButton;

    public void enterUsername(String username) {
        usernameField.type(username);
    }

    public void enterPassword(String password) {
        passwordField.type(password);
    }

    public void clickLoginButton() {
        loginButton.click();
    }
}
