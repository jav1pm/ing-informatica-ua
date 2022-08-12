package ejercicio2.conPO;

import org.openqa.selenium.By;
import org.openqa.selenium.WebDriver;
import org.openqa.selenium.WebElement;

public class HomePage {

    WebDriver driver;
    WebElement account;
    WebElement login;

    public HomePage(WebDriver driver) {
        this.driver = driver;
        this.driver.get("http://demo-store.seleniumacademy.com/");
        account = driver.findElement(By.xpath("//*[@id=\"header\"]/div/div[2]/div/a"));
    }

    public CustomerLoginPage goLogin() {
        account.click();
        login = driver.findElement(By.linkText("Log In"));
        login.click();
        return new CustomerLoginPage(driver);
    }

    public String getHomePageTitle() {
        return driver.getTitle();
    }
}
