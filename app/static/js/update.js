$(document).ready(function() {
    // var tab_url = $('#analyser_data').load($('#analyser_data').attr("data-url"));
    $.ajaxSetup({
        cache: false
    });
    //event.preventDefault();
    setInterval(function() {
        $('#analyser_table').load("http://127.0.0.1:8000/medidor/table");
    }, 2000);
});
