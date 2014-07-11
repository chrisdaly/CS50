/**
 * service.js
 *
 * Computer Science 50
 * Problem Set 8
 *
 * Implements a shuttle service.
 */

// starting score
var SCORE = 0;

// id of a timeout function
var timeoutID;

// time left in seconds
var TIME = 60;

// default height
var HEIGHT = 0.8;

// default latitude
var LATITUDE = 42.3745615030193;

// default longitude
var LONGITUDE = -71.11803936751632;

// default heading
var HEADING = 1.757197490907891;

// default number of seats
var SEATS = 10;

// default velocity
var VELOCITY = 50;

// global reference to shuttle's marker on 2D map
var bus = null;

// global reference to 3D Earth
var earth = null;

// global reference to 2D map
var map = null;

// global reference to shuttle
var shuttle = null;

// load version 1 of the Google Earth API
google.load("earth", "1");

// load version 3 of the Google Maps API
google.load("maps", "3", {other_params: "sensor=false"});

// once the window has loaded
$(window).load(function() {

    // listen for keydown anywhere in body
    $(document.body).keydown(function(event) {
        return keystroke(event, true);
    });

    // listen for keyup anywhere in body
    $(document.body).keyup(function(event) {
        return keystroke(event, false);
    });

    // listen for click on Drop Off button
    $("#dropoff").click(function(event) {
        dropoff();
    });

    // listen for click on Pick Up button
    $("#pickup").click(function(event) {
        pickup();
    });

    // load application
    load();

    countdown();


});

// unload application
$(window).unload(function() {
    unload();
});

// unique interval ID
var nIntervId;

/**
 * Every second changeText is called.
 */
function countdown() {
  nIntervId = setInterval(changeText, 1000);
}

/**
 * Time is checked, colourized and updated.
 */
function changeText() {

    // create the string to insert into the DOM
    var time_left = "Time left = " + TIME + " seconds";
    $("#time").html(time_left);

    // if the time is up then end the game
    if (TIME == 0)
    {
        alert("GAME OVER");
        stopCountdown();
    }

    else
    {
        // decrement the time by a second
        TIME -= 1
    }

    // select the time element and make it flash
    var oElem = document.getElementById("time");
    oElem.style.color = oElem.style.color == "red" ? "blue" : "red";
}

/**
 * Stops the countdown function.
 */
function stopCountdown() {
  clearInterval(nIntervId);
}

/**
 * Converts a house name to a css class.
 */
function make_house_class(str)
{
    // truncate the string at the space
    n = str.search(" ");
    return str.substring(0, n);
}

/**
 * Renders seating chart.
 */
function chart()
{
    // create the string to insert into the DOM
    var score = "Score = " + SCORE + " points";
    $("#score").html(score);

    var html = "<ol class='passengers' start='0'>";
    for (var i = 0; i < shuttle.seats.length; i++)
    {
        if (shuttle.seats[i] == null)
        {
            html += "<li class='house_empty'>-</li>";
        }
        else
        {
            this_class = make_house_class(shuttle.seats[i].house);
            html += "<li class='house_" + this_class + "'>" + shuttle.seats[i].name + "&nbsp" + shuttle.seats[i].house + "</li>";
        }
    }
    html += "</ol>";
    $("#chart").html(html);
}

/**
 * Drops up passengers if their stop is nearby.
 */
function dropoff()
{
    $("#announcements").html("Dropoff!!");
    // loop through all the passengers, checking their houses
    for (var i = 0; i < shuttle.seats.length; i++)
    {
        // flag for a dropoff
        dropoff_done = false;

        shuttle.seat = shuttle.seats[i]

        // only check a seat if there is a person in it
        if (shuttle.seat != null)
        {   
            // initialize person variables
            person = shuttle.seats[i];

            // check if the person's house is in the HOUSES list
            house = HOUSES[person.house];

            if (house != null)
            {
                // set the coords
                lat = house.lat;
                lng = house.lng;
            }

            // calculate the distance between the shuttle and the house
            var house_dis = shuttle.distance(lat, lng);


            // condition: house close to the shuttle
            if (house_dis < 30.0)
            {
                // empty the seat
                shuttle.seats[i] = null;

                // change the flag
                dropoff_done = true;

                // update the chart
                chart(); 

                // increase the score
                SCORE += 100;

                $("#announcements").html("+100 points"); 

                // give the user more time
                TIME += 30;
            }
        }
    }

    // if there was no dropoff then announce it
    if (dropoff_done == false)
    {
        $("#announcements").html("No one was dropped off!"); 
    }

}

/**
 * Called if Google Earth fails to load.
 */
function failureCB(errorCode) 
{
    // report error unless plugin simply isn't installed
    if (errorCode != ERR_CREATE_PLUGIN)
    {
        alert(errorCode);
    }
}

/**
 * Handler for Earth's frameend event.
 */
function frameend() 
{
    shuttle.update();
}

/**
 * Called once Google Earth has loaded.
 */
function initCB(instance) 
{
    // retain reference to GEPlugin instance
    earth = instance;

    // specify the speed at which the camera moves
    earth.getOptions().setFlyToSpeed(100);

    // show buildings
    earth.getLayerRoot().enableLayerById(earth.LAYER_BUILDINGS, true);

    // disable terrain (so that Earth is flat)
    earth.getLayerRoot().enableLayerById(earth.LAYER_TERRAIN, false);

    // prevent mouse navigation in the plugin
    earth.getOptions().setMouseNavigationEnabled(false);

    // instantiate shuttle
    shuttle = new Shuttle({
        heading: HEADING,
        height: HEIGHT,
        latitude: LATITUDE,
        longitude: LONGITUDE,
        planet: earth,
        seats: SEATS,
        velocity: VELOCITY
    });

    // synchronize camera with Earth
    google.earth.addEventListener(earth, "frameend", frameend);

    // synchronize map with Earth
    google.earth.addEventListener(earth.getView(), "viewchange", viewchange);

    // update shuttle's camera
    shuttle.updateCamera();

    // show Earth
    earth.getWindow().setVisibility(true);

    // render seating chart
    chart();

    // populate Earth with passengers and houses
    populate();
}

/**
 * Handles keystrokes.
 */
function keystroke(event, state)
{
    $("#announcements").html("va va voom"); 
    // ensure we have event
    if (!event)
    {
        event = window.event;
    }

    // left arrow
    if (event.keyCode == 37)
    {
        shuttle.states.turningLeftward = state;
        return false;
    }

    // up arrow
    else if (event.keyCode == 38)
    {
        shuttle.states.tiltingUpward = state;
        return false;
    }

    // right arrow
    else if (event.keyCode == 39)
    {
        shuttle.states.turningRightward = state;
        return false;
    }

    // down arrow
    else if (event.keyCode == 40)
    {
        shuttle.states.tiltingDownward = state;
        return false;
    }

    // A, a
    else if (event.keyCode == 65 || event.keyCode == 97)
    {
        shuttle.states.slidingLeftward = state;
        return false;
    }

    // D, d
    else if (event.keyCode == 68 || event.keyCode == 100)
    {
        shuttle.states.slidingRightward = state;
        return false;
    }
  
    // S, s
    else if (event.keyCode == 83 || event.keyCode == 115)
    {
        shuttle.states.movingBackward = state;     
        return false;
    }

    // W, w
    else if (event.keyCode == 87 || event.keyCode == 119)
    {
        shuttle.states.movingForward = state;    
        return false;
    }
  
    return true;
}

/**
 * Loads application.
 */
function load()
{
    // embed 2D map in DOM
    var latlng = new google.maps.LatLng(LATITUDE, LONGITUDE);
    map = new google.maps.Map($("#map").get(0), {
        center: latlng,
        disableDefaultUI: true,
        mapTypeId: google.maps.MapTypeId.ROADMAP,
        scrollwheel: false,
        zoom: 17,
        zoomControl: true
    });

    // prepare shuttle's icon for map
    bus = new google.maps.Marker({
        icon: "https://maps.gstatic.com/intl/en_us/mapfiles/ms/micons/bus.png",
        map: map,
        title: "you are here"
    });

    // embed 3D Earth in DOM
    google.earth.createInstance("earth", initCB, failureCB);
}

/**
 * Picks up nearby passengers.
 */
function pickup()
{
    $("#announcements").html("Pickup!!");
    // loop through all the passengers, checking their distance from the shuttle
    for (var i in PASSENGERS)
    {
        // initialize person variables
        person = PASSENGERS[i];

        // flag for a nearby person
        person_near = false;

        // flag for an empty seat check
        empty_seat = false;

        // only check a person if they are still present on the map
        if (person.marker.map != null)
        {
            // condition 1: no freshmen
            if (person.house in HOUSES)
            {
                // set coords
                lat = person.placemark.getGeometry().getLatitude();
                lng = person.placemark.getGeometry().getLongitude();

                // calculate the distance between the shuttle and the person
                var dis = shuttle.distance(lat, lng);

                // condition 2: person close to the shuttle
                if (dis < 15.0)
                {   
                    $("#announcements").html("Person Near!");

                    // change the flag
                    person_near = true

                    //  loop through the seats on the shuttle, checking for empty ones
                    for (var j = 0; j < shuttle.seats.length; j++ )
                    {
                        // condition 3: available seat on the shuttle
                        if (shuttle.seats[j] == null)
                        {
                            // change the flag
                            empty_seat = true

                            // move the person to the seat
                            shuttle.seats[j] = person;

                            // remove that person from the 3d map
                            var features = earth.getFeatures();
                            features.removeChild(person.placemark);

                            // remove that person from the 2d map
                            person.marker.setMap(null);

                            // update the chart
                            chart();

                            // give the user more time
                            TIME += 5;
                        
                            break;
                        }
                    }
                }
            }

            else
            {
                $("#announcements").html("Sorry, no freshmen!");
            }   
        }
        // if the shuttle is full then announce it
        if (empty_seat == false)
        {
            $("#announcements").html("No room left!");
        }
    }

    // if the shuttle is not within 15m of a person then announce it
    if (person_near == false)
    {
        $("#announcements").html("No one is near!"); 
    }
}

/**
 * Populates Earth with passengers and houses.
 */
function populate()
{
    // mark houses
    for (var house in HOUSES)
    {
        // plant house on map
        new google.maps.Marker({
            icon: "https://google-maps-icons.googlecode.com/files/home.png",
            map: map,
            position: new google.maps.LatLng(HOUSES[house].lat, HOUSES[house].lng),
            title: house
        });
    }

    // get current URL, sans any filename
    var url = window.location.href.substring(0, (window.location.href.lastIndexOf("/")) + 1);

    // scatter passengers
    for (var i = 0; i < PASSENGERS.length; i++)
    {
        // pick a random building
        var building = BUILDINGS[Math.floor(Math.random() * BUILDINGS.length)];

        // prepare placemark
        var placemark = earth.createPlacemark("");
        placemark.setName(PASSENGERS[i].name + " to " + PASSENGERS[i].house);

        // prepare icon
        var icon = earth.createIcon("");
        icon.setHref(url + "/img/" + PASSENGERS[i].username + ".jpg");

        // prepare style
        var style = earth.createStyle("");
        style.getIconStyle().setIcon(icon);
        style.getIconStyle().setScale(4.0);

        // prepare stylemap
        var styleMap = earth.createStyleMap("");
        styleMap.setNormalStyle(style);
        styleMap.setHighlightStyle(style);

        // associate stylemap with placemark
        placemark.setStyleSelector(styleMap);

        // prepare point
        var point = earth.createPoint("");
        point.setAltitudeMode(earth.ALTITUDE_RELATIVE_TO_GROUND);
        point.setLatitude(building.lat);
        point.setLongitude(building.lng);
        point.setAltitude(0.0);

        // associate placemark with point
        placemark.setGeometry(point);

        // add placemark to Earth
        earth.getFeatures().appendChild(placemark);

        // add marker to map
        var marker = new google.maps.Marker({
            icon: "https://maps.gstatic.com/intl/en_us/mapfiles/ms/micons/man.png",
            map: map,
            position: new google.maps.LatLng(building.lat, building.lng),
            title: PASSENGERS[i].name + " at " + building.name
        });

        // add marker to the passenger type
        PASSENGERS[i].marker = marker

        // add placemarker to the passenger type
        PASSENGERS[i].placemark = placemark
    }
}

/**
 * Handler for Earth's viewchange event.
 */
function viewchange() 
{
    // keep map centered on shuttle's marker
    var latlng = new google.maps.LatLng(shuttle.position.latitude, shuttle.position.longitude);
    map.setCenter(latlng);
    bus.setPosition(latlng);
}

/**
 * Unloads Earth.
 */
function unload()
{
    google.earth.removeEventListener(earth.getView(), "viewchange", viewchange);
    google.earth.removeEventListener(earth, "frameend", frameend);
}
