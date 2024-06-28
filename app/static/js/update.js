$(document).ready(function() {
    // var tab_url = $('#analyser_data').load($('#analyser_data').attr("data-url"));
    var base_url = window.location.origin;

    $.ajaxSetup({
        cache: false
    });
    //event.preventDefault();
    setInterval(function() {
        $('#analyser_table').load(base_url + "/medidor/table");
    }, 2000);
});
