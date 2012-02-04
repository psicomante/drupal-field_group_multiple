<?php


function field_group_multiple_field_ui_overview_form_alter(&$form, &$form_state, $display_overview = FALSE) {
  Logger::log("");

  $form['#validate'][] = "field_group_multiple_field_overview_validate";
  $form['#submit'][] = "field_group_multiple_field_overview_submit";
}

function field_group_multiple_field_overview_validate($form, &$form_state) {
  _field_group_multiple_field_ui_overview_operation($form, $form_state, 'validate');
}


function field_group_multiple_field_overview_submit($form, &$form_state) {
  _field_group_multiple_field_ui_overview_operation($form, $form_state, 'submit');
}


function _field_group_multiple_field_ui_overview_operation($form, &$form_state, $op) {
  Logger::log($op);

  if(!isset($form_state['field_group_params']) || empty($form_state['field_group_params'])) return;
  //if(!isset($form['#groups']) || empty($form['#groups'])) return;
  Logger::log($form_state);

  $field_groups = $form_state['field_group_params']->groups;
  //Logger::log($field_groups);

  foreach($field_groups as $group_name => $group){
    if(_is_field_group_multiple($group->format_type)){
      $function = '_' . $group->format_type . '_format_' . $op;
      Logger::log($function);
      if(function_exists($function)) {
        Logger::log("exists");
        $function($form, $form_state, $group);
      }
    }
  }

}



/**
 * Default settings
 */
function _field_group_multiple_default_format_settings($group){

}

/**
 * Default summary
 */
function _field_group_multiple_default_format_summary($group){

}

function _field_group_multiple_default_format_validate($form, &$form_state, $group){

}

function _field_group_multiple_default_format_submit($form, &$form_state, $group){

}


/**
 * Table settings
 */
function _field_group_multiple_table_format_settings($group){
  Logger::log("");

  $form = array(
      'instance_settings' => array(
        '#tree' => TRUE,
        '#weight' => 2,
    ),
  );

  $field_group_types = field_group_formatter_info();
  $mode = $group->mode == 'form' ? 'form' : 'display';
  $formatter = $field_group_types[$mode][$group->format_type];

  return $form;
}


function _field_group_multiple_table_format_summary($group){
  Logger::log("");
  return "TEST";
}

function _field_group_multiple_table_format_validate($form, &$form_state, $group){
  _field_group_multiple_default_format_validate($form, $form_state, $group);

  Logger::log("");
  form_set_error($group->group_name,"abc");
}

function _field_group_multiple_table_format_submit($form, &$form_state, $group){
  _field_group_multiple_default_format_submit($form, $form_state, $group);

  Logger::log("");
}
