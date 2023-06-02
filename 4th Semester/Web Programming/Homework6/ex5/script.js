const loadDoc = (method, url, callback) => {
    $.ajax({
        type: method,
        url: url,
        success: callback
    })
}

const convertToHtmlnt = (str) => {
    convertedStr = '';
    for (let i = 0; i < str.length; i++) {
        if (str[i] === '<') {
            convertedStr += '&lt;';
        } else if (str[i] === '>') {
            convertedStr += '&gt;';
        } else {
            convertedStr += str[i];
        }
    }
    return convertedStr;
}

const createChildren = (ul, files, dirName = '', clickable = true) => {
    for (let j = 0; j < files.length; j++) {
        const li = $("<li></li>");
        let txt = files[j];
        if (dirName !== '') {
            txt = dirName + "//" + txt;
        }
        let liText = null;
        if (clickable) {
            liText = $("<p></p>");
            liText.append(txt);
            liText.addClass("clickable");
            liText.click(function () {
                if (!$(this).hasClass("clicked")) {
                    $(this).addClass("clicked");
                    clickFile($(this).parent(), txt);
                } else {
                    $(this).removeClass("clicked");
                    $(this).parent().children("ul").empty();
                }
            });
        } else {
            liText = $("<textarea readonly cols=\"80\" rows=\"10\"></textarea>")
            liText.append(convertToHtmlnt(txt));
        }
        li.append(liText);
        ul.append(li);
    }
}

const clickFile = (parent, dirName) => {
    console.log(dirName);
    const ul = $("<ul></ul>");
    parent.append(ul);
    loadDoc("GET", "files.php?path=" + dirName, function(response) {
        try {
            const files = $.parseJSON(response);
            createChildren(ul, files, dirName=dirName);
        } catch (error) {
            createChildren(ul, [response], dirName='', clickable=false);
        }
    });
}

const loadFiles = (response) => {
    const ul = $("#root");
    var files = $.parseJSON(response);
    createChildren(ul, files);
}

$(document).ready(() => {
    loadDoc("GET", "files.php?path", loadFiles);
})