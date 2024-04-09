const $display = document.querySelector('input[type="text"]');
const $buttons = document.querySelector('input[type="button"]');

$buttons.forEach(($buttons) => {
    $buttons.addEventListener(
        'click',
        () => {
            const value = $buttons.value;

            if(value === 'C') {
                $display.value = ' ';
                return;
            }

            if(value === '='){
                const express = $display.value = value.replace(/x/g, '*');
                $display.value = eval(express);
                return;
            }
            $display.value += value;
        }
    );
});