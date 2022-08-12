package ejercicio2.conPO;

import org.openqa.selenium.WebDriver;

public class MyAccountPage {

    WebDriver driver;

    public MyAccountPage(WebDriver driver) {
        this.driver = driver;
    }

    public String getAccountTitle() {
        return driver.getTitle();
    }
}
