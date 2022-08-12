package ejercicio2.conPO;

import org.openqa.selenium.By;
import org.openqa.selenium.WebDriver;
import org.openqa.selenium.WebElement;

public class CustomerLoginPage {

    WebDriver driver;
    WebElement email;
    WebElement password;
    WebElement buttonLogin;
    WebElement error_msg;

    public CustomerLoginPage(WebDriver driver) {
        this.driver = driver;
        email = driver.findElement(By.cssSelector("input#email"));
        password = driver.findElement(By.cssSelector("input#pass"));
        buttonLogin = driver.findElement(By.name("send"));
    }

    public MyAccountPage loginOK(String user, String pass) {
        email.sendKeys(user);
        password.sendKeys(pass);
        buttonLogin.click();
        return new MyAccountPage(driver);
    }

    public String loginFailed(String user, String pass) {
        email.sendKeys(user);
        password.sendKeys(pass);
        buttonLogin.click();
        error_msg = driver.findElement(By.className("error-msg"));
        return error_msg.getText();
    }

    public String getCustomerLoginTitle() {
        return driver.getTitle();
    }
}
