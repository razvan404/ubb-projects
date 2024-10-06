package parabank.pages;
import net.serenitybdd.core.annotations.findby.By;
import net.thucydides.core.annotations.DefaultUrl;
import net.serenitybdd.core.pages.WebElementFacade;

import net.serenitybdd.core.annotations.findby.FindBy;

import net.thucydides.core.pages.PageObject;
import org.openqa.selenium.WebDriver;

import java.util.List;

@DefaultUrl("https://parabank.parasoft.com/parabank/openaccount.htm")
public class OpenAccountPage extends PageObject{
    @FindBy(id = "type")
    private WebElementFacade accountTypeDropdown;

    @FindBy(id = "fromAccountId")
    private WebElementFacade existingAccountDropdown;

    @FindBy(css = "input.button[value='Open New Account']")
    private WebElementFacade openNewAccountButton;

    @FindBy(css = "#openAccountResult h1.title")
    private WebElementFacade accountOpenedMessage;

    @FindBy(css = "a[href='overview.htm']")
    private WebElementFacade overviewPageButton;

    @FindBy(id = "accountTable")
    private WebElementFacade existingAccountTable;

    @FindBy(css = "a[href='logout.htm']")
    private WebElementFacade logoutButton;

    public void clickLogoutButton() {
        logoutButton.click();
    }

    public void selectAccountType(String accountType) {
        accountTypeDropdown.selectByVisibleText(accountType);
    }

    public void selectExistingAccount(String existingAccount) {
        existingAccountDropdown.selectByVisibleText(existingAccount);
    }

    public void clickOpenNewAccountButton() {
        openNewAccountButton.click();
    }

    public boolean isAccountOpened() {
        return accountOpenedMessage.containsText("Account Opened!");
    }

    public void clickOverviewButton() {
        overviewPageButton.click();
    }

    public int selectNumberOfRowsOverviewTable() {
        List<WebElementFacade> rows = existingAccountTable.thenFindAll(By.tagName("tr"));
        return rows.size();
    }
}
