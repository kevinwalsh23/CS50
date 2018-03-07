// Google Map
var map;

// markers for map
var markers = [];

// info window
//var info = new google.maps.InfoWindow();

// execute when the DOM is fully loaded
$(function() {

    // styles for map
    // https://developers.google.com/maps/documentation/javascript/styling
    var styles = [

        // hide Google's labels
        {
            featureType: "all",
            elementType: "labels",
            stylers: [
                {visibility: "off"}
            ]
        },

        // hide roads

    ];

    // options for map
    // https://developers.google.com/maps/documentation/javascript/reference#MapOptions
    var options = {
        center: {lat: 40.743298, lng: -73.986407}, // Empire State Building, NY
        disableDefaultUI: true,
        mapTypeId: google.maps.MapTypeId.ROADMAP,
        maxZoom: 20,
        panControl: true,
        styles: styles,
        zoom: 13,
        zoomControl: true
    };

    // get DOM node in which map will be instantiated
    var canvas = $("#map-canvas").get(0);

    // instantiate map
    map = new google.maps.Map(canvas, options);

    // configure UI once Google Map is idle (i.e., loaded)
    google.maps.event.addListenerOnce(map, "idle", configure);

    markers.push(kmarker);
    
  
    // options for map
    update();

   //google.maps.event.addListener(marker, "click", function() { loadInfoWindow(place, marker) });

}
    

);

/**
 * Adds marker for place to map.
 */
 
function addMarker(place)
{
   // var stuff = "http://maps.google.com/mapfiles/kml/pal3/icon40.png";
    var myLatLng = new google.maps.LatLng(parseFloat(place.latitude), parseFloat(place.longitude));
    
    var kmarker = new google.maps.Marker({
    position: myLatLng,
    map: map,
    title:  "Hello",
    labelContent:  "Goodbye",
    labelAnchor: new google.maps.Point(27, 60),
    labelClass: "labels",
    //icon: icon
  });
  
   //google.maps.event.addListener(marker, "click", function() { loadInfoWindow(place, marker) });
    
    markers.push(kmarker);
 
}

function removeMarkers()
{
    var lentil_markers = markers.length;
    for (var i = 0; i < lentil_markers; i++){
        markers[i].setMap(null);
    }
    
    markers.length = 0;
    // TODO
}

function configure()
{
    // update UI after map has been dragged
    google.maps.event.addListener(map, "dragend", function() {

        // if info window isn't open
        // http://stackoverflow.com/a/12410385
        if (!info.getMap || !info.getMap())
        {
            update();
        }
    });

    // update UI after zoom level changes
    google.maps.event.addListener(map, "zoom_changed", function() {
        update();
    });
    
    update();
}

function update() 
{
    $.getJSON(Flask.url_for("mapsearch"))
    .done(function(data, textStatus, jqXHR) {

        console.log('hello where am i ', data);
        
       // remove old markers from map
       removeMarkers();

       // add new markers to map
       for (var i = 0; i < data.length; i++)
       {
           addMarker(data[i]);
       }
    })
    .fail(function(jqXHR, textStatus, errorThrown) {
        console.log('what is this', jqXHR);
        // log error to browser's console
        console.log(errorThrown.toString());
    });

}
