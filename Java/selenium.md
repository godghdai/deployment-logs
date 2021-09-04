```java
package src.xigua.spider;

import com.alibaba.fastjson.JSON;
import com.alibaba.fastjson.JSONArray;
import com.alibaba.fastjson.JSONObject;
import org.openqa.selenium.By;
import org.openqa.selenium.JavascriptExecutor;
import org.openqa.selenium.WebDriver;
import org.openqa.selenium.WebElement;
import org.openqa.selenium.chrome.ChromeDriver;
import org.openqa.selenium.support.ui.WebDriverWait;
import src.xigua.core.Media;
import src.xigua.core.Result;

import java.time.Duration;
import java.util.Comparator;
import java.util.Optional;

import static org.openqa.selenium.support.ui.ExpectedConditions.visibilityOfElementLocated;

public class XiguaPlayUrlSpider {

    public static Result getResult(String url) {
        System.setProperty("webdriver.chrome.driver", "C:\\Users\\yzd\\Downloads\\Compressed\\chromedriver_win32\\chromedriver.exe");
        WebDriver driver = new ChromeDriver();
        WebDriverWait wait = new WebDriverWait(driver, Duration.ofSeconds(10));

        try {
            driver.get(url);
            wait.until(visibilityOfElementLocated(By.cssSelector("#player_default")));
            JavascriptExecutor driver_js = ((JavascriptExecutor) driver);
            String js = "var data=window._SSR_HYDRATED_DATA.anyVideo.gidInformation.packerData.video.videoResource.dash.dynamic_video;" +
                    "return JSON.stringify(data);";
            String result = (String) driver_js.executeScript(js);
            JSONObject jb = JSON.parseObject(result);
            String video_url = getPlayUrl(jb.getJSONArray("dynamic_video_list"));
            System.out.println(video_url);
            String audio_url = getPlayUrl(jb.getJSONArray("dynamic_audio_list"));
            System.out.println(audio_url);

            WebElement element = driver.findElement(By.cssSelector(".videoTitle h1"));
            return new Result(element.getText(),video_url,audio_url);
            //System.out.println(JSON.toJSONString(jb, true));
            //Thread.sleep(13000);

        } finally {
            driver.quit();
        }

    }

    private static String getPlayUrl(JSONArray medias) {
        Optional<Media> op_media = medias.stream().
                map(Media::fromJSONObject).
                min(Comparator.comparingInt(o -> o.bitrate)
                );
        return op_media.isPresent()?op_media.get().url:"";
    }
}


```
