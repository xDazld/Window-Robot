const char Main_Page[] PROGMEM = R"====(
<!DOCTYPE html>
<html lang="en">
    <head>
        <meta charset="utf-8">
        <meta name="viewport" content="width=device-width, initial-scale=1.0, shrink-to-fit=no">
        <title>Window Robot</title>
        <style>
            body {
                background-color: black;
            }
            .buttons {
                padding: 10vh 5vw 10vh 5vw;
                margin-top: 5vh;
                border-radius: 10px;
                background-color: lightblue;
                border: none;
                color: rgb(81, 81, 81);
                font-size: 5vh;
                font-family: 'tahoma';
                font-weight: bold;
            }
            section {
                text-align: center;
            }
        </style>
    </head>
    <body>
        <section>
            <a href="/stepperON"><button class="buttons">Stepper Wind</button></a>
            <a href="/stepperOFF"><button class="buttons">Stepper Unwind</button></a>
        </section>
        <script src="assets/bootstrap/js/bootstrap.min.js"></script>
    </body>
</html>
)====";